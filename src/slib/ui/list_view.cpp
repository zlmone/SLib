#include "../../../inc/slib/ui/list_view.h"

#include "../../../inc/slib/ui/core.h"
#include "../../../inc/slib/core/log.h"

#define MAX_ITEMS_VISIBLE 500
#define MAX_MID_HEIGHT 1000000

#if defined(SLIB_PLATFORM_IS_WIN32) || defined(SLIB_PLATFORM_IS_IOS)
#else
#	define USE_CONTENT_VIEW
#endif

SLIB_UI_NAMESPACE_BEGIN

class _ListContentView : public ViewGroup
{
public:
	WeakRef<ListView> m_lv;
	
public:
	// override
	void dispatchDraw(Canvas* canvas);
	
	// override
	void onResizeChild(View* child, sl_ui_len width, sl_ui_len height);
	
};

sl_ui_len IListViewAdapter::getAverageItemHeight(ListView* lv)
{
	return 0;
}

SLIB_DEFINE_OBJECT(ListView, VerticalScrollView)

ListView::ListView()
{
	SLIB_REFERABLE_CONSTRUCTOR
	
	ScrollView::setOccurringClick(sl_false);
	
	m_flagResetAdapter = sl_true;
	m_flagRefreshItems = sl_true;
	
	m_viewsVisibleItems = (Ref<View>*)(Base::createZeroMemory(sizeof(Ref<View>)*MAX_ITEMS_VISIBLE*4));
	m_viewsGoDownItems = m_viewsVisibleItems + MAX_ITEMS_VISIBLE;
	m_viewsGoUpItems = m_viewsGoDownItems + MAX_ITEMS_VISIBLE;
	m_viewsFreeItems = m_viewsGoUpItems + MAX_ITEMS_VISIBLE;
	
	m_heightsVisibleItems = (sl_ui_len*)(Base::createMemory(sizeof(sl_ui_len)*MAX_ITEMS_VISIBLE*5));
	m_heightsTopItems = m_heightsVisibleItems + MAX_ITEMS_VISIBLE;
	m_heightsBottomItems = m_heightsTopItems + MAX_ITEMS_VISIBLE;
	m_heightsGoDownItems = m_heightsBottomItems + MAX_ITEMS_VISIBLE;
	m_heightsGoUpItems = m_heightsGoDownItems + MAX_ITEMS_VISIBLE;
	
	_initStatus();
	
	m_contentView = new _ListContentView;
	m_contentView->setLayoutEnabled(sl_false);
	m_contentView->m_lv = this;
#ifdef USE_CONTENT_VIEW
	ScrollView::setContentView(m_contentView);
#else
	addChild(m_contentView, sl_false);
	setCreatingChildInstances(sl_true);
#endif
	
#if defined(SLIB_PLATFORM_IS_WIN32)
	setOpaque(sl_true, sl_false);
#endif

}

ListView::~ListView()
{
	for (sl_size i = 0; i < MAX_ITEMS_VISIBLE*3; i++) {
		if (m_viewsVisibleItems[i].isNotNull()) {
			m_viewsVisibleItems[i].setNull();
		}
	}
	Base::freeMemory(m_viewsVisibleItems);
	Base::freeMemory(m_heightsVisibleItems);
}

void ListView::setAdapter(const Ptr<IListViewAdapter>& adapter)
{
	m_adapter = adapter;
	m_flagResetAdapter = sl_true;
	UI::dispatchToUiThread(SLIB_CALLBACK_WEAKREF(ListView, _checkUpdateContent, this, sl_false));
}

void ListView::refreshItems()
{
	m_flagRefreshItems = sl_true;
	UI::dispatchToUiThread(SLIB_CALLBACK_WEAKREF(ListView, _checkUpdateContent, this, sl_false));
}

void ListView::onScroll(sl_scroll_pos _x, sl_scroll_pos _y)
{
	sl_ui_pos y = (sl_ui_pos)(_y);
	if (Math::isAlmostZero(y - m_lastScrollY)) {
		return;
	}
	UI::dispatchToUiThread(SLIB_CALLBACK_WEAKREF(ListView, _layoutItemViews, this, sl_false, sl_true, sl_false));
}

void ListView::onResize(sl_ui_len x, sl_ui_len y)
{
	UI::dispatchToUiThread(SLIB_CALLBACK_WEAKREF(ListView, _layoutItemViews, this, sl_false, sl_false, sl_false));
}

void ListView::_checkUpdateContent(sl_bool fromDraw)
{
	if (!(UI::isUiThread())) {
		return;
	}
	if (m_flagResetAdapter) {
		m_flagResetAdapter = sl_false;
		m_flagRefreshItems = sl_false;
		_resetAdapter();
		_layoutItemViews(fromDraw, sl_false, sl_true);
		return;
	}
	if (m_flagRefreshItems) {
		m_flagRefreshItems = sl_false;
		_layoutItemViews(fromDraw, sl_false, sl_true);
		return;
	}
}

void ListView::_initStatus()
{
	m_countTotalItems = 0;
	m_indexFirstItem = 0;
	m_yFirstItem = 0;
	m_countVisibleItems = 0;
	m_averageItemHeight = 0;
	m_averageMidItemHeight = 0;
	m_heightTotalItems = 0;
	m_lastScrollY = 0;
	for (sl_uint32 i = 0; i < MAX_ITEMS_VISIBLE; i++) {
		m_heightsTopItems[i] = 0;
		m_heightsBottomItems[i] = 0;
	}
}

void ListView::_resetAdapter()
{
	m_contentView->removeAllChildren();
	setContentHeight(0);
	for (sl_size i = 0; i < m_countVisibleItems; i++) {
		m_viewsVisibleItems[i].setNull();
	}
	_initStatus();
	scrollTo(0, 0);
}

static sl_ui_len _ListView_getTotalHeights(sl_uint64 count, sl_ui_len averageHeight, sl_ui_len* topHeights, sl_ui_len* bottomHeights, double& averageMidHeight)
{
	averageMidHeight = (double)(averageHeight);
	sl_uint32 i;
	sl_ui_len s = 0;
	for (i = 0; i < MAX_ITEMS_VISIBLE; i++) {
		if (i >= count) {
			return s;
		}
		sl_ui_len h = topHeights[i];
		if (h <= 0) {
			h = averageHeight;
		}
		s += h;
	}
	count -= MAX_ITEMS_VISIBLE;
	if (count == 0) {
		return s;
	}
	for (i = 0; i < MAX_ITEMS_VISIBLE; i++) {
		if (i >= count) {
			return s;
		}
		sl_ui_len h = bottomHeights[i];
		if (h <= 0) {
			h = averageHeight;
		}
		s += h;
	}
	count -= MAX_ITEMS_VISIBLE;
	if (count == 0 || averageHeight == 0) {
		return s;
	}
	double fCount = (double)count;
	double mid = fCount * (double)(averageHeight);
	sl_ui_len _mid;
	if (mid > MAX_MID_HEIGHT) {
		_mid = MAX_MID_HEIGHT;
		averageMidHeight = MAX_MID_HEIGHT / fCount;
	} else {
		_mid = (sl_ui_len)(count) * averageHeight;
	}
	s += _mid;
	return s;
}

static sl_ui_len _ListView_getAverageHeight(sl_uint64 count, sl_ui_len* topHeights, sl_ui_len* bottomHeights)
{
	sl_uint32 i;
	sl_ui_len s = 0;
	sl_uint32 n = 0;
	for (i = 0; i < MAX_ITEMS_VISIBLE; i++) {
		if (i >= count) {
			break;
		}
		sl_ui_len h = topHeights[i];
		if (h > 0) {
			s += h;
			n++;
		}
	}
	if (count > MAX_ITEMS_VISIBLE) {
		count -= MAX_ITEMS_VISIBLE;
		if (count > 0) {
			for (i = 0; i < MAX_ITEMS_VISIBLE; i++) {
				if (i >= count) {
					break;
				}
				sl_ui_len h = bottomHeights[i];
				if (h > 0) {
					s += h;
					n++;
				}
			}
		}
	}
	if (n == 0) {
		return 0;
	}
	return s / n;
}

static sl_ui_pos _ListView_getYPositionOfItem(sl_uint64 index, sl_uint64 count, sl_ui_len averageHeight, double averageMidHeight, sl_ui_len totalHeight, sl_ui_len* topHeights, sl_ui_len* bottomHeights)
{
	if (index > count) {
		index = count;
	}
	if (index <= MAX_ITEMS_VISIBLE) {
		sl_ui_len y = 0;
		sl_uint32 n = (sl_uint32)index;
		for (sl_uint32 i = 0; i < n; i++) {
			sl_ui_len h = topHeights[i];
			if (h <= 0) {
				h = averageHeight;
			}
			y += h;
		}
		return y;
	}
	if (count - index <= MAX_ITEMS_VISIBLE) {
		sl_ui_len y = 0;
		sl_uint32 n = (sl_uint32)(count - index);
		for (sl_uint32 i = 0; i < n; i++) {
			sl_ui_len h = bottomHeights[i];
			if (h <= 0) {
				h = averageHeight;
			}
			y += h;
		}
		if (totalHeight > y) {
			y = totalHeight - y;
		} else {
			y = 0;
		}
		return y;
	}
	sl_ui_len y = 0;
	for (sl_uint32 i = 0; i < MAX_ITEMS_VISIBLE; i++) {
		sl_ui_len h = topHeights[i];
		if (h <= 0) {
			h = averageHeight;
		}
		y += h;
	}
	return y + (sl_ui_len)((double)(index - MAX_ITEMS_VISIBLE) * averageMidHeight);
}

template <class T>
static void _ListView_pushArrayLeft(T* arr, sl_uint64 sizeArr, sl_uint32 capacityArr, T value, sl_uint64 _count)
{
	if (_count >= capacityArr) {
		for (sl_uint32 i = 0; i < capacityArr; i++) {
			arr[i] = value;
		}
	} else {
		sl_uint32 count = (sl_uint32)_count;
		sl_uint64 _n = sizeArr + count;
		if (_n > capacityArr) {
			_n = capacityArr;
		}
		sl_uint32 n = (sl_uint32)_n;
		n -= count;
		sl_uint32 p = n - 1;
		sl_uint32 i;
		for (i = 0; i < n; i++) {
			arr[p+count] = arr[p];
			p--;
		}
		for (i = 0; i < count; i++) {
			arr[i] = value;
		}
	}
}

template <class T>
static void _ListView_pushArrayRight(T* arr, sl_uint64 sizeArr, sl_uint32 capacityArr, T value, sl_uint64 _count)
{
	if (_count >= capacityArr) {
		for (sl_uint32 i = 0; i < capacityArr; i++) {
			arr[i] = value;
		}
	} else {
		sl_uint32 count = (sl_uint32)_count;
		sl_uint32 i;
		sl_uint32 n;
		if (sizeArr > capacityArr) {
			n = capacityArr;
		} else {
			n = (sl_uint32)sizeArr;
		}
		n -= count;
		for (i = 0; i < n; i++) {
			arr[i] = arr[i + count];
		}
		n += count;
		for (; i < n; i++) {
			arr[i] = value;
		}
	}
}

void ListView::_layoutItemViews(sl_bool fromDraw, sl_bool fromScroll, sl_bool flagRefresh)
{
	if (!(UI::isUiThread())) {
		return;
	}
	
	sl_ui_pos widthListView = getWidth();
	sl_ui_pos heightListView = getHeight();
	
	if (widthListView <= 0 || heightListView <= 0) {
		return;
	}
	
	PtrLocker<IListViewAdapter> adapter(m_adapter);
	
	if (adapter.isNotNull()) {
		
		View* contentView = m_contentView.ptr;

		Ref<View>* viewsVisibleItems = m_viewsVisibleItems;
		sl_ui_len* heightsVisibleItems = m_heightsVisibleItems;
		sl_ui_len* heightsTopItems = m_heightsTopItems;
		sl_ui_len* heightsBottomItems = m_heightsBottomItems;
		Ref<View>* viewsGoDownItems = m_viewsGoDownItems;
		sl_ui_len* heightsGoDownItems = m_heightsGoDownItems;
		Ref<View>* viewsGoUpItems = m_viewsGoUpItems;
		sl_ui_len* heightsGoUpItems = m_heightsGoUpItems;
		Ref<View>* viewsFreeItems = m_viewsFreeItems;
		
		sl_uint64 lastCountTotalItems = m_countTotalItems;
		sl_ui_len lastHeightTotalItems = m_heightTotalItems;
		sl_uint64 lastIndexFirstItem = m_indexFirstItem;
		sl_ui_len lastAverageItemHeight = m_averageItemHeight;
		double lastAverageMidItemHeight = m_averageMidItemHeight;
		sl_uint32 lastCountVisibleItems = m_countVisibleItems;
		
		sl_uint32 countFreeViews = 0;
		sl_uint32 countGoDownViews = 0;
		sl_uint32 countGoUpViews = 0;
		
		sl_uint64 countTotalItems = lastCountTotalItems;
		sl_ui_len heightTotalItems = lastHeightTotalItems;
		sl_bool flagClearAll = sl_false;
		
		sl_ui_pos yGoDown = 0;
		sl_uint64 indexGoDown = 0;
		sl_ui_pos yGoUp = 0;
		sl_uint64 indexGoUp = 0;
		
		sl_ui_pos scrollY = (sl_ui_pos)(getScrollY());
		if (fromScroll) {
			if (Math::isAlmostZero(scrollY - m_lastScrollY)) {
				return;
			}
		}
		sl_ui_pos originalScrollY = scrollY;
		
		if (flagRefresh) {
			
			countTotalItems = adapter->getItemsCount(this);
			
			flagClearAll = sl_true;
			
			// shift bottom heights when count is changed
			if (lastCountTotalItems != countTotalItems) {
				if (countTotalItems > lastCountTotalItems) {
					sl_uint64 off = countTotalItems - lastCountTotalItems;
					_ListView_pushArrayLeft<sl_ui_len>(heightsBottomItems, lastCountTotalItems, MAX_ITEMS_VISIBLE, 0, off);
				} else {
					sl_uint64 off = lastCountTotalItems - countTotalItems;
					_ListView_pushArrayRight<sl_ui_len>(heightsBottomItems, lastCountTotalItems, MAX_ITEMS_VISIBLE, 0, off);
				}
			}
			
			heightTotalItems = _ListView_getTotalHeights(countTotalItems, lastAverageItemHeight, heightsTopItems, heightsBottomItems, lastAverageMidItemHeight);
			
			// free visible views
			for (sl_uint32 iItem = 0; iItem < lastCountVisibleItems; iItem++) {
				Ref<View> view = viewsVisibleItems[iItem];
				if (view.isNotNull()) {
					viewsFreeItems[countFreeViews] = view;
					countFreeViews++;
					viewsVisibleItems[iItem].setNull();
				}
			}
			
		} else {
			
			// removes scrolled-over items
			sl_ui_pos yItem = m_yFirstItem;
			sl_uint32 iItem;
			for (iItem = 0; iItem < lastCountVisibleItems; iItem++) {
				sl_ui_pos h = heightsVisibleItems[iItem];
				if (yItem + h > scrollY) {
					break;
				}
				yItem += h;
				Ref<View> view = viewsVisibleItems[iItem];
				if (view.isNotNull()) {
					viewsFreeItems[countFreeViews] = view;
					countFreeViews++;
					viewsVisibleItems[iItem].setNull();
				}
			}
			
			yGoUp = yItem;
			indexGoUp = lastIndexFirstItem + iItem;
			sl_uint32 iStart = iItem;
			
			// reuse visible items
			for (; iItem < lastCountVisibleItems && yItem < scrollY + heightListView; iItem++) {
				Ref<View> view = viewsVisibleItems[iItem];
				sl_ui_len h = _measureItemHeight(view, heightListView);
				yItem += h;
				viewsGoDownItems[countGoDownViews] = view;
				heightsGoDownItems[countGoDownViews] = h;
				countGoDownViews++;
				viewsVisibleItems[iItem].setNull();
			}
			

			yGoDown = yItem;
			indexGoDown = lastIndexFirstItem + iItem;
			
			if (iStart >= lastCountVisibleItems || yGoUp >= scrollY + heightListView) {
				flagClearAll = sl_true;
			}
			
			// free remaining visible views
			for (; iItem < lastCountVisibleItems; iItem++) {
				Ref<View> view = viewsVisibleItems[iItem];
				if (view.isNotNull()) {
					viewsFreeItems[countFreeViews] = view;
					countFreeViews++;
					viewsVisibleItems[iItem].setNull();
				}
			}
		}
		
		if (scrollY > heightTotalItems) {
			scrollY = heightTotalItems;
		}
		
		// all of former visible items is scrolled over, so have to find index and y position
		if (flagClearAll) {
			
			sl_ui_pos yTop = 0;
			sl_ui_pos yBottom = heightTotalItems;
			
			sl_ui_pos y = 0;
			sl_uint64 index = 0;
			sl_bool flagFound = sl_false;
			
			if (scrollY != 0 && lastAverageItemHeight > 0) {
				
				sl_uint32 i;
				for (i = 0; i < MAX_ITEMS_VISIBLE; i++) {
					if (i >= countTotalItems) {
						break;
					}
					sl_ui_pos h = heightsTopItems[i];
					if (h <= 0) {
						h = lastAverageItemHeight;
					}
					if (yTop + h > scrollY) {
						y = yTop;
						index = i;
						flagFound = sl_true;
						break;
					}
					h = heightsBottomItems[i];
					if (h <= 0) {
						h = lastAverageItemHeight;
					}
					if (yBottom - h < scrollY) {
						y = yBottom;
						index = countTotalItems - i;
						flagFound = sl_true;
						break;
					}
					yTop += h;
					yBottom -= h;
				}
				
				if (!flagFound) {
					y = scrollY;
					if (i < MAX_ITEMS_VISIBLE || Math::isAlmostZero(lastAverageMidItemHeight)) {
						index = 0;
					} else {
						double no = (double)(y - yTop) / lastAverageMidItemHeight;
						if (no < 0) {
							no = 0;
						}
						index = MAX_ITEMS_VISIBLE + (sl_uint64)(no);
						if (index > countTotalItems) {
							index = countTotalItems;
						}
					}
				}
			}
			
			yGoDown = y;
			indexGoDown = index;
			yGoUp = y;
			indexGoUp = index;
			
		}

		// Go Up
		{
			while (yGoUp > scrollY && indexGoUp > 0 && countGoUpViews < MAX_ITEMS_VISIBLE) {
				Ref<View> viewFree;
				if (countFreeViews > 0) {
					viewFree = viewsFreeItems[countFreeViews-1];
					if (viewFree.isNull()) {
						countFreeViews--;
					}
				}
				Ref<View> view = adapter->getView(this, indexGoUp - 1, viewFree.ptr);
				sl_ui_len h = _measureItemHeight(view, heightListView);
				viewsGoUpItems[countGoUpViews] = view;
				heightsGoUpItems[countGoUpViews] = h;
				countGoUpViews++;
				yGoUp -= h;
				indexGoUp--;
				if (view == viewFree && viewFree.isNotNull()) {
					countFreeViews--;
					viewsFreeItems[countFreeViews].setNull();
				}
			}
		}
		
		sl_uint64 indexStart = indexGoUp;
		sl_ui_pos yStart = yGoUp;

		// Go Down
		{
			while (yGoDown < scrollY + heightListView && indexGoDown < countTotalItems && countGoDownViews < MAX_ITEMS_VISIBLE) {
				Ref<View> viewFree;
				if (countFreeViews > 0) {
					viewFree = viewsFreeItems[countFreeViews-1];
					if (viewFree.isNull()) {
						countFreeViews--;
					}
				}
				Ref<View> view = adapter->getView(this, indexGoDown, viewFree.ptr);
				sl_ui_len h = _measureItemHeight(view, heightListView);
				viewsGoDownItems[countGoDownViews] = view;
				heightsGoDownItems[countGoDownViews] = h;
				countGoDownViews++;
				yGoDown += h;
				indexGoDown++;
				if (view == viewFree && viewFree.isNotNull()) {
					countFreeViews--;
					viewsFreeItems[countFreeViews].setNull();
				}
			}
		}
		
		// Merge to visible items
		sl_uint32 countVisibleItems = 0;
		{
			sl_uint32 i;
			sl_uint32 k = countGoUpViews - 1;
			for (i = 0; i < countGoUpViews && countVisibleItems < MAX_ITEMS_VISIBLE; i++) {
				viewsVisibleItems[countVisibleItems] = viewsGoUpItems[k];
				heightsVisibleItems[countVisibleItems] = heightsGoUpItems[k];
				countVisibleItems++;
				viewsGoUpItems[k].setNull();
				k--;
			}
			for (i = 0; i < countGoDownViews && countVisibleItems < MAX_ITEMS_VISIBLE; i++) {
				viewsVisibleItems[countVisibleItems] = viewsGoDownItems[i];
				heightsVisibleItems[countVisibleItems] = heightsGoDownItems[i];
				countVisibleItems++;
				viewsGoDownItems[i].setNull();
			}
		}
		
		// Save top&bottom heights
		{
			for (sl_uint32 i = 0; i < countVisibleItems; i++) {
				sl_uint64 index = indexStart + i;
				if (index < MAX_ITEMS_VISIBLE) {
					heightsTopItems[(sl_uint32)index] = heightsVisibleItems[i];
				}
				if (index < countTotalItems) {
					if (countTotalItems - index <= MAX_ITEMS_VISIBLE) {
						heightsBottomItems[(sl_uint32)(countTotalItems - 1 - index)] = heightsVisibleItems[i];
					}
				}
			}
		}
		sl_ui_len averageItemHeight = adapter->getAverageItemHeight(this);
		if (averageItemHeight <= 0) {
			averageItemHeight = _ListView_getAverageHeight(countTotalItems, heightsTopItems, heightsBottomItems);
		}
		double averageMidItemHeight = averageItemHeight;
		heightTotalItems = _ListView_getTotalHeights(countTotalItems, averageItemHeight, heightsTopItems, heightsBottomItems, averageMidItemHeight);

		// readjust scroll position
		if (!flagClearAll) {
			if (scrollY < heightListView || scrollY + 2 * heightListView >= heightTotalItems) {
				sl_ui_pos scrollOffset = scrollY - yStart;
				sl_ui_pos yStartNew = _ListView_getYPositionOfItem(indexStart, countTotalItems, averageItemHeight, averageMidItemHeight, heightTotalItems, heightsTopItems, heightsBottomItems);
				if (Math::abs(yStartNew - yStart) > averageItemHeight/10) {
					yStart = yStartNew;
					scrollY = yStartNew + scrollOffset;
				}
			}
		}

		// remove free views
		{
			for (sl_size iItem = 0; iItem < countFreeViews; iItem++) {
				contentView->removeChild(viewsFreeItems[iItem]);
				viewsFreeItems[iItem].setNull();
			}
		}
		
		// layout views
		{
			sl_ui_pos y;
#if defined(USE_CONTENT_VIEW)
			y = yStart;
#else
			y = yStart - scrollY;
#endif
			for (sl_size i = 0; i < countVisibleItems; i++) {
				Ref<View> view = viewsVisibleItems[i];
				sl_ui_pos b = y + heightsVisibleItems[i];
				if (view.isNotNull()) {
					UIRect rect;
					rect.left = 0;
					rect.right = widthListView;
					rect.top = y;
					rect.bottom = b;
					rect.fixSizeError();
					if (view->getParent() != contentView) {
						view->setFrame(rect, sl_false);
						contentView->addChild(view, !fromDraw);
					} else {
						view->setFrame(rect, !fromDraw);
					}
				}
				y = b;
			}
		}
		
		m_countTotalItems = countTotalItems;
		m_indexFirstItem = indexStart;
		m_yFirstItem = yStart;
		m_countVisibleItems = countVisibleItems;
		m_averageItemHeight = averageItemHeight;
		m_averageMidItemHeight = averageMidItemHeight;
		m_heightTotalItems = heightTotalItems;
		m_lastScrollY = scrollY;

		if (!(Math::isAlmostZero((sl_ui_pos)(getContentHeight()) - (sl_ui_pos)heightTotalItems)) || !(Math::isAlmostZero((sl_ui_pos)(getContentWidth()) - (sl_ui_pos)widthListView))) {
			setContentSize((sl_scroll_pos)widthListView, (sl_scroll_pos)heightTotalItems);
		}
		if (!(Math::isAlmostZero(scrollY - originalScrollY))) {
			scrollTo(0, (sl_scroll_pos)scrollY);
		}
		
#if !defined(USE_CONTENT_VIEW)
#if defined(SLIB_PLATFORM_IS_IOS)
		UIRect rcContent = getBounds();
		rcContent.top += scrollY;
		rcContent.bottom += scrollY;
		rcContent.fixSizeError();
		contentView->setFrame(rcContent, sl_false);
#else
		contentView->setFrame(getBounds(), sl_false);
#endif
#endif
		if (!fromDraw) {
			contentView->invalidate();
		}
	}
}

sl_ui_len ListView::_measureItemHeight(const Ref<View>& itemView, sl_ui_len heightList)
{
	sl_ui_len ret = 0;
	if (itemView.isNotNull()) {
		SizeMode mode = itemView->getHeightMode();
		switch (mode) {
			case SizeMode::Filling:
				ret = heightList;
				break;
			case SizeMode::Weight:
				ret = (sl_ui_len)((sl_real)heightList * itemView->getHeightWeight());
				break;
			case SizeMode::Wrapping:
				itemView->measureLayout();
				ret = itemView->getMeasuredHeight();
				break;
			default:
				ret = itemView->getHeight();
				break;
		}
	}
	sl_ui_len minItemHeight = heightList / (MAX_ITEMS_VISIBLE + 1);
	if (ret < minItemHeight) {
		ret = minItemHeight;
	}
	return ret;
}

void _ListContentView::dispatchDraw(Canvas* canvas)
{
	Ref<ListView> lv = m_lv;
	if (lv.isNotNull()) {
		lv->_layoutItemViews(sl_true, sl_false, sl_false);
	}
	ViewGroup::dispatchDraw(canvas);
}

void _ListContentView::onResizeChild(View* child, sl_ui_len width, sl_ui_len height)
{
	Ref<ListView> lv = m_lv;
	if (lv.isNotNull()) {
		UI::dispatchToUiThread(SLIB_CALLBACK_WEAKREF(ListView, _layoutItemViews, lv.ptr, sl_false, sl_false, sl_false));
	}
}

SLIB_UI_NAMESPACE_END
