#ifndef LIBJPEG_SLIB_H
#define LIBJPEG_SLIB_H

#ifndef SLIB_LIBJPEG_NO_PREFIX

#define jpeg_std_error		                      slib_jpeg_std_error
#define jpeg_CreateCompress	                      slib_jpeg_CreateCompress
#define jpeg_CreateDecompress	                      slib_jpeg_CreateDecompress
#define jpeg_destroy_compress	                      slib_jpeg_destroy_compress
#define jpeg_destroy_decompress                      slib_jpeg_destroy_decompress
#define jpeg_stdio_dest		                      slib_jpeg_stdio_dest
#define jpeg_stdio_src		                      slib_jpeg_stdio_src
#define jpeg_mem_dest		                      slib_jpeg_mem_dest
#define jpeg_mem_src		                      slib_jpeg_mem_src
#define jpeg_set_defaults	                      slib_jpeg_set_defaults
#define jpeg_set_colorspace	                      slib_jpeg_set_colorspace
#define jpeg_default_colorspace                      slib_jpeg_default_colorspace
#define jpeg_set_quality	                      slib_jpeg_set_quality
#define jpeg_set_linear_quality                      slib_jpeg_set_linear_quality
#define jpeg_default_qtables	                      slib_jpeg_default_qtables
#define jpeg_add_quant_table	                      slib_jpeg_add_quant_table
#define jpeg_quality_scaling	                      slib_jpeg_quality_scaling
#define jpeg_simple_progression                      slib_jpeg_simple_progression
#define jpeg_suppress_tables	                      slib_jpeg_suppress_tables
#define jpeg_alloc_quant_table                      slib_jpeg_alloc_quant_table
#define jpeg_alloc_huff_table	                      slib_jpeg_alloc_huff_table
#define jpeg_start_compress	                      slib_jpeg_start_compress
#define jpeg_write_scanlines	                      slib_jpeg_write_scanlines
#define jpeg_finish_compress	                      slib_jpeg_finish_compress
#define jpeg_calc_jpeg_dimensions                      slib_jpeg_calc_jpeg_dimensions
#define jpeg_write_raw_data	                      slib_jpeg_write_raw_data
#define jpeg_write_marker	                      slib_jpeg_write_marker
#define jpeg_write_m_header	                      slib_jpeg_write_m_header
#define jpeg_write_m_byte	                      slib_jpeg_write_m_byte
#define jpeg_write_tables	                      slib_jpeg_write_tables
#define jpeg_read_header	                      slib_jpeg_read_header
#define jpeg_start_decompress	                      slib_jpeg_start_decompress
#define jpeg_read_scanlines	                      slib_jpeg_read_scanlines
#define jpeg_finish_decompress	                      slib_jpeg_finish_decompress
#define jpeg_read_raw_data	                      slib_jpeg_read_raw_data
#define jpeg_has_multiple_scans	                      slib_jpeg_has_multiple_scans
#define jpeg_start_output	                      slib_jpeg_start_output
#define jpeg_finish_output	                      slib_jpeg_finish_output
#define jpeg_input_complete	                      slib_jpeg_input_complete
#define jpeg_new_colormap	                      slib_jpeg_new_colormap
#define jpeg_consume_input	                      slib_jpeg_consume_input
#define jpeg_core_output_dimensions	                      slib_jpeg_core_output_dimensions
#define jpeg_calc_output_dimensions	                      slib_jpeg_calc_output_dimensions
#define jpeg_save_markers	                      slib_jpeg_save_markers
#define jpeg_set_marker_processor	                      slib_jpeg_set_marker_processor
#define jpeg_read_coefficients	                      slib_jpeg_read_coefficients
#define jpeg_write_coefficients	                      slib_jpeg_write_coefficients
#define jpeg_copy_critical_parameters	                      slib_jpeg_copy_critical_parameters
#define jpeg_abort_compress	                      slib_jpeg_abort_compress
#define jpeg_abort_decompress	                      slib_jpeg_abort_decompress
#define jpeg_abort		                      slib_jpeg_abort
#define jpeg_destroy		                      slib_jpeg_destroy
#define jpeg_resync_to_restart	                      slib_jpeg_resync_to_restart

#define jinit_compress_master               slib_jinit_compress_master
#define jinit_c_master_control               slib_jinit_c_master_control
#define jinit_c_main_controller               slib_jinit_c_main_controller
#define jinit_c_prep_controller               slib_jinit_c_prep_controller
#define jinit_c_coef_controller               slib_jinit_c_coef_controller
#define jinit_color_converter               slib_jinit_color_converter
#define jinit_downsampler	               slib_jinit_downsampler
#define jinit_forward_dct	               slib_jinit_forward_dct
#define jinit_huff_encoder	               slib_jinit_huff_encoder
#define jinit_arith_encoder	               slib_jinit_arith_encoder
#define jinit_marker_writer	               slib_jinit_marker_writer
#define jinit_master_decompress               slib_jinit_master_decompress
#define jinit_d_main_controller               slib_jinit_d_main_controller
#define jinit_d_coef_controller               slib_jinit_d_coef_controller
#define jinit_d_post_controller               slib_jinit_d_post_controller
#define jinit_input_controller               slib_jinit_input_controller
#define jinit_marker_reader	               slib_jinit_marker_reader
#define jinit_huff_decoder	               slib_jinit_huff_decoder
#define jinit_arith_decoder	               slib_jinit_arith_decoder
#define jinit_inverse_dct	               slib_jinit_inverse_dct
#define jinit_upsampler		               slib_jinit_upsampler
#define jinit_color_deconverter               slib_jinit_color_deconverter
#define jinit_1pass_quantizer               slib_jinit_1pass_quantizer
#define jinit_2pass_quantizer               slib_jinit_2pass_quantizer
#define jinit_merged_upsampler               slib_jinit_merged_upsampler
#define jinit_memory_mgr	               slib_jinit_memory_mgr
#define jdiv_round_up		               slib_jdiv_round_up
#define jround_up		               slib_jround_up
#define jzero_far		               slib_jzero_far
#define jcopy_sample_rows	               slib_jcopy_sample_rows
#define jcopy_block_row		               slib_jcopy_block_row
#define jpeg_zigzag_order	               slib_jpeg_zigzag_order
#define jpeg_natural_order	               slib_jpeg_natural_order
#define jpeg_natural_order7	               slib_jpeg_natural_order7
#define jpeg_natural_order6	               slib_jpeg_natural_order6
#define jpeg_natural_order5	               slib_jpeg_natural_order5
#define jpeg_natural_order4	               slib_jpeg_natural_order4
#define jpeg_natural_order3	               slib_jpeg_natural_order3
#define jpeg_natural_order2	               slib_jpeg_natural_order2
#define jpeg_aritab		               slib_jpeg_aritab

#define jpeg_get_small		           slib_jpeg_get_small
#define jpeg_free_small		           slib_jpeg_free_small
#define jpeg_get_large		           slib_jpeg_get_large
#define jpeg_free_large		           slib_jpeg_free_large
#define jpeg_mem_available	           slib_jpeg_mem_available
#define jpeg_open_backing_store	           slib_jpeg_open_backing_store
#define jpeg_mem_init		           slib_jpeg_mem_init
#define jpeg_mem_term		          slib_jpeg_mem_term

#define jpeg_std_message_table        slib_jpeg_std_message_table

#define jpeg_fdct_islow		slib_jpeg_fdct_islow
#define jpeg_fdct_ifast		slib_jpeg_fdct_ifast
#define jpeg_fdct_float		slib_jpeg_fdct_float
#define jpeg_fdct_7x7		slib_jpeg_fdct_7x7
#define jpeg_fdct_6x6		slib_jpeg_fdct_6x6
#define jpeg_fdct_5x5		slib_jpeg_fdct_5x5
#define jpeg_fdct_4x4		slib_jpeg_fdct_4x4
#define jpeg_fdct_3x3		slib_jpeg_fdct_3x3
#define jpeg_fdct_2x2		slib_jpeg_fdct_2x2
#define jpeg_fdct_1x1		slib_jpeg_fdct_1x1
#define jpeg_fdct_9x9		slib_jpeg_fdct_9x9
#define jpeg_fdct_10x10		slib_jpeg_fdct_10x10
#define jpeg_fdct_11x11		slib_jpeg_fdct_11x11
#define jpeg_fdct_12x12		slib_jpeg_fdct_12x12
#define jpeg_fdct_13x13		slib_jpeg_fdct_13x13
#define jpeg_fdct_14x14		slib_jpeg_fdct_14x14
#define jpeg_fdct_15x15		slib_jpeg_fdct_15x15
#define jpeg_fdct_16x16		slib_jpeg_fdct_16x16
#define jpeg_fdct_16x8		slib_jpeg_fdct_16x8
#define jpeg_fdct_14x7		slib_jpeg_fdct_14x7
#define jpeg_fdct_12x6		slib_jpeg_fdct_12x6
#define jpeg_fdct_10x5		slib_jpeg_fdct_10x5
#define jpeg_fdct_8x4		slib_jpeg_fdct_8x4
#define jpeg_fdct_6x3		slib_jpeg_fdct_6x3
#define jpeg_fdct_4x2		slib_jpeg_fdct_4x2
#define jpeg_fdct_2x1		slib_jpeg_fdct_2x1
#define jpeg_fdct_8x16		slib_jpeg_fdct_8x16
#define jpeg_fdct_7x14		slib_jpeg_fdct_7x14
#define jpeg_fdct_6x12		slib_jpeg_fdct_6x12
#define jpeg_fdct_5x10		slib_jpeg_fdct_5x10
#define jpeg_fdct_4x8		slib_jpeg_fdct_4x8
#define jpeg_fdct_3x6		slib_jpeg_fdct_3x6
#define jpeg_fdct_2x4		slib_jpeg_fdct_2x4
#define jpeg_fdct_1x2		slib_jpeg_fdct_1x2
#define jpeg_idct_islow		slib_jpeg_idct_islow
#define jpeg_idct_ifast		slib_jpeg_idct_ifast
#define jpeg_idct_float		slib_jpeg_idct_float
#define jpeg_idct_7x7		slib_jpeg_idct_7x7
#define jpeg_idct_6x6		slib_jpeg_idct_6x6
#define jpeg_idct_5x5		slib_jpeg_idct_5x5
#define jpeg_idct_4x4		slib_jpeg_idct_4x4
#define jpeg_idct_3x3		slib_jpeg_idct_3x3
#define jpeg_idct_2x2		slib_jpeg_idct_2x2
#define jpeg_idct_1x1		slib_jpeg_idct_1x1
#define jpeg_idct_9x9		slib_jpeg_idct_9x9
#define jpeg_idct_10x10		slib_jpeg_idct_10x10
#define jpeg_idct_11x11		slib_jpeg_idct_11x11
#define jpeg_idct_12x12		slib_jpeg_idct_12x12
#define jpeg_idct_13x13		slib_jpeg_idct_13x13
#define jpeg_idct_14x14		slib_jpeg_idct_14x14
#define jpeg_idct_15x15		slib_jpeg_idct_15x15
#define jpeg_idct_16x16		slib_jpeg_idct_16x16
#define jpeg_idct_16x8		slib_jpeg_idct_16x8
#define jpeg_idct_14x7		slib_jpeg_idct_14x7
#define jpeg_idct_12x6		slib_jpeg_idct_12x6
#define jpeg_idct_10x5		slib_jpeg_idct_10x5
#define jpeg_idct_8x4		slib_jpeg_idct_8x4
#define jpeg_idct_6x3		slib_jpeg_idct_6x3
#define jpeg_idct_4x2		slib_jpeg_idct_4x2
#define jpeg_idct_2x1		slib_jpeg_idct_2x1
#define jpeg_idct_8x16		slib_jpeg_idct_8x16
#define jpeg_idct_7x14		slib_jpeg_idct_7x14
#define jpeg_idct_6x12		slib_jpeg_idct_6x12
#define jpeg_idct_5x10		slib_jpeg_idct_5x10
#define jpeg_idct_4x8		slib_jpeg_idct_4x8
#define jpeg_idct_3x6		slib_jpeg_idct_3x6
#define jpeg_idct_2x4		slib_jpeg_idct_2x4
#define jpeg_idct_1x2		slib_jpeg_idct_1x2

#endif

#endif