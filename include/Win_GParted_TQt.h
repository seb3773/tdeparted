/* Copyright (C) 2026
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GPARTED_WIN_GPARTED_TQT_H
#define GPARTED_WIN_GPARTED_TQT_H

#include "GParted_Core.h"
#include "Operation.h"

#include <tqmainwindow.h>

#include <tqaction.h>
#include <tqcombobox.h>

#include <tqlabel.h>
#include <tqdialog.h>
#include <tqframe.h>
#include <tqgroupbox.h>
#include <tqlistview.h>
#include <tqpopupmenu.h>
#include <tqpushbutton.h>
#include <tqsplitter.h>
#include <tqtoolbutton.h>
#include <tqtoolbar.h>
#include <tqprogressbar.h>
#include <tqthread.h>

#include <tdetoolbar.h>
#include <tdetoolbarbutton.h>
#include <tqtimer.h>

#include <tqmutex.h>

#include <map>

#include <vector>

namespace GParted
{

struct OpsUpdate_TQt
{
	Glib::ustring treepath;
	Glib::ustring description;
	Glib::ustring elapsed;
	OperationDetailStatus status;
	double fraction;
	int pb_running;
	Glib::ustring pb_text;
};

class Win_GParted_TQt : public TQMainWindow
{
	TQ_OBJECT

public:
	Win_GParted_TQt( const std::vector<Glib::ustring> & user_devices );
	~Win_GParted_TQt();

	Win_GParted_TQt(const Win_GParted_TQt& src) = delete;
	Win_GParted_TQt& operator=(const Win_GParted_TQt& rhs) = delete;

private slots:
	void menu_quit();
	void menu_about();
	void menu_help_contents();
	void menu_view_device_information();
	void menu_view_pending_operations();
	void menu_view_filesystem_support();
	void start_initial_scan();
	void menu_device_refresh_devices();
	void menu_device_create_partition_table();
	void menu_device_create_disk_image();
	void menu_device_restore_disk_image();
	void menu_device_secure_erase();
	void menu_device_load_disk_image();
	void menu_device_detach_virtual_device();
	void menu_device_smart_infos();
	void menu_device_simple_benchmark();
	void menu_gparted_devices_select( int id );
	void menu_partition_format_to( int id );
	void action_new();
	void action_delete();
	void action_resize_move();
	void action_copy();
	void action_paste();
	void action_partition_create_image();
	void action_partition_restore_image();
	void action_partition_secure_erase();
	void action_toggle_crypt_busy_state();
	void action_toggle_fs_busy_state();
	void menu_partition_mount_on( int id );
	void action_name_partition();
	void action_manage_flags();
	void action_check();
	void action_label_filesystem();
	void action_change_uuid();
	void action_undo();
	void action_clear_operations();
	void action_apply();
	void action_export_commands();
	void action_information();
	void combo_devices_changed( int index );
	void details_selection_changed( TQListViewItem *item );
	void details_context_menu( TQListViewItem *item, const TQPoint &pos, int col );
	void pending_ops_context_menu( TQListViewItem *item, const TQPoint &pos, int col );

private:
	friend class VisualDiskWidget;
	void ops_on_signal_update( const OperationDetail &od );
	bool quit_check_operations();
	void init_menubar();
	void init_toolbar();
	void init_layout();
	void init_statusbar();
	void refresh_devices();
	void refresh_details_table();
	void refresh_device_information();
	void update_window_title();
	void select_partition_in_details( const Partition *p );
	void select_partition_from_visualdisk( const Partition *p );
	void popup_partition_menu_at_cursor();
	void visualdisk_activate_information();
	void update_valid_actions();
	void refresh_pending_operations_ui();

protected:
	void closeEvent( TQCloseEvent *e );
	void refresh_visual();
	bool add_operation( const Device &device, std::unique_ptr<Operation> operation );
	bool merge_operation( const Operation &candidate );
	bool operations_affect_same_partition( const Operation &first_op, const Operation &second_op );

	GParted_Core m_core;
	std::vector<Device> m_devices;
	int m_current_device;
	Device m_display_device;
	OperationVector m_operations;
	Partition *m_copied_partition;
	unsigned short m_new_count;

	TQWidget  *m_central_widget;
	TQSplitter *m_splitter_v;
	TQSplitter *m_splitter_h;
	TQFrame   *m_visualdisk_frame;
	TQWidget  *m_visualdisk_widget;
	TQLabel   *m_visualdisk_scanning_label;
	TQFrame   *m_deviceinfo_frame;
	TQLabel   *m_lbl_dev_model;
	TQLabel   *m_lbl_dev_serial;
	TQLabel   *m_lbl_dev_type;
	TQLabel   *m_lbl_dev_size;
	TQLabel   *m_lbl_dev_path;
	TQLabel   *m_lbl_dev_disktype;
	TQLabel   *m_lbl_dev_heads;
	TQLabel   *m_lbl_dev_sectors;
	TQLabel   *m_lbl_dev_cylinders;
	TQLabel   *m_lbl_dev_total_sectors;
	TQLabel   *m_lbl_dev_sector_size;
	TQFrame   *m_details_frame;
	TQWidget  *m_details_device_header;
	TQLabel   *m_details_device_icon;
	TQLabel   *m_details_device_label;
	TQListView *m_details_list;
	TQFrame   *m_operations_frame;
	TQPushButton *m_btn_export_commands;
	TQListView *m_operations_list;
	TDEToolBar  *m_toolbar;
	TDEToolBarButton *m_btn_refresh;
	TQComboBox *m_combo_devices;

	TQPopupMenu *m_menu_edit;
	TQPopupMenu *m_menu_view;
	TQPopupMenu *m_menu_device;
	TQPopupMenu *m_menu_partition;
	TQPopupMenu *m_menu_gparted;
	TQPopupMenu *m_menu_gparted_devices;
	TQPopupMenu *m_menu_partition_format_to;
	TQPopupMenu *m_menu_partition_mount_on;
	std::vector<int> m_menu_gparted_devices_ids;
	std::vector<int> m_menu_partition_format_to_ids;
	std::vector<FSType> m_menu_partition_format_to_fstypes;
	std::vector<int> m_menu_partition_mount_on_ids;
	std::vector<Glib::ustring> m_menu_partition_mount_on_mountpoints;
	int m_menu_view_device_info_id;
	int m_menu_view_pending_ops_id;
	int m_menu_device_refresh_devices_id;
	int m_menu_device_create_table_id;
	int m_menu_device_create_image_id;
	int m_menu_device_restore_image_id;
	int m_menu_device_secure_erase_id;
	int m_menu_device_load_image_id;
	int m_menu_device_detach_virtual_id;
	int m_menu_device_smart_infos_id;
	int m_menu_device_simple_benchmark_id;
	int m_menu_gparted_devices_id;
	int m_menu_partition_new_id;
	int m_menu_partition_delete_id;
	int m_menu_partition_resize_id;
	int m_menu_partition_copy_id;
	int m_menu_partition_paste_id;
	int m_menu_partition_create_image_id;
	int m_menu_partition_restore_image_id;
	int m_menu_partition_secure_erase_id;
	int m_menu_partition_format_id;
	int m_menu_partition_toggle_crypt_id;
	int m_menu_partition_toggle_fs_id;
	int m_menu_partition_mount_on_id;
	int m_menu_partition_name_id;
	int m_menu_partition_flags_id;
	int m_menu_partition_check_id;
	int m_menu_partition_label_id;
	int m_menu_partition_uuid_id;
	int m_menu_partition_info_id;
	int m_menu_edit_undo_id;
	int m_menu_edit_clear_id;
	int m_menu_edit_apply_id;
	const Partition *m_selected_partition;
	Glib::ustring m_selected_partition_path;
	Sector m_selected_partition_sector_start;
	Sector m_selected_partition_sector_end;
	int m_selected_partition_type;
	int m_in_selection_sync;

	TDEToolBarButton *m_btn_new;
	TDEToolBarButton *m_btn_delete;
	TDEToolBarButton *m_btn_resize_move;
	TDEToolBarButton *m_btn_copy;
	TDEToolBarButton *m_btn_paste;
	TDEToolBarButton *m_btn_mount;
	TDEToolBarButton *m_btn_undo;
	TDEToolBarButton *m_btn_apply;
	std::vector<sigc::connection> m_ops_connections;
	std::map<Glib::ustring, TQListViewItem*> m_ops_items;
	TQPopupMenu *m_ops_popup;
	int m_ops_popup_undo_id;
	int m_ops_popup_clear_id;
	int m_ops_popup_apply_id;
	int m_ops_popup_close_id;

	struct VirtualAttach_TQt
	{
		Glib::ustring dev_path;
		Glib::ustring image_path;
		int backend;
	};
	std::vector<VirtualAttach_TQt> m_virtual_attaches;
};

class ApplyWorker_TQt : public TQThread
{
public:
	ApplyWorker_TQt( GParted_Core *core, const OperationVector &operations );
	void run() override;
	void cancel();

	int get_current_op();
	bool get_success();
	void get_updates( std::vector<OpsUpdate_TQt> &updates );

private:
	void on_signal_update( const OperationDetail &od );

	GParted_Core *m_core;
	const OperationVector &m_operations;
	TQMutex m_state_mutex;
	bool m_success;
	bool m_cancel_requested;
	int m_current_op;

	TQMutex m_queue_mutex;
	std::vector<OpsUpdate_TQt> m_update_queue;
};

class Dialog_Progress_TQt : public TQDialog
{
	TQ_OBJECT

public:
	class ProgressWithText : public TQWidget
	{
	public:
		ProgressWithText( TQWidget *parent );
		void set_fraction( double f );
		void set_text( const TQString &t );
		void set_pulse_step( int step );
		void pulse();

		TQProgressBar *bar;
		TQLabel *label;
		int pulse_pos;
		int pulse_step;
	};

	Dialog_Progress_TQt( const std::vector<Device> &devices, const OperationVector &operations, TQWidget *parent );
	bool run_modal_apply( GParted_Core &core );

private slots:
	void on_details_toggled( bool on );
	void on_start_apply();
	void on_cancel();
	void on_cancel_timeout();
	void on_pulse();
	void on_save();
	void on_ui_timeout();
	void on_worker_finished();

private:
	void force_cancel_current();

protected:
	void closeEvent( TQCloseEvent *e );
	void accept();

	const std::vector<Device> &m_devices;
	const OperationVector &m_operations;
	bool m_success;
	bool m_cancel;
	unsigned int m_curr_op;
	unsigned int m_warnings;
	bool m_details_visible;
	bool m_running;
	bool m_force_cancel;
	GParted_Core *m_core;

	// Widgets — same order as the GTK widget hierarchy
	TQVBoxLayout *m_vbox;
	TQLabel *m_label_intro;
	TQLabel *m_label_current;         // bold: current operation description
	ProgressWithText *m_progress_current;  // current op progress (pulsable)
	TQLabel *m_label_current_sub;     // italic: current sub-operation
	TQLabel *m_label_completed;       // bold "Completed Operations:"
	ProgressWithText *m_progress_all;  // overall progress with text
	TQPushButton *m_expander_button;  // ▶/▼ expander toggle
	TQWidget *m_details_container;    // container for the scrolled treeview
	TQListView *m_details_list;       // treeview for operation details
	TQPushButton *m_btn_cancel;
	TQPushButton *m_btn_save;
	TQPushButton *m_btn_close;
	TQTimer *m_cancel_timer;
	TQTimer *m_pulse_timer;
	int m_cancel_countdown;
	int m_compact_height;             // dialog height without details

	ApplyWorker_TQt *m_worker;
	TQTimer *m_ui_timer;

	std::vector<sigc::connection> m_connections;
	std::map<Glib::ustring, TQListViewItem*> m_items;
	TQPixmap m_icon_execute;
	TQPixmap m_icon_success;
	TQPixmap m_icon_error;
	TQPixmap m_icon_info;
	TQPixmap m_icon_warning;
};

struct ImagingUpdate_TQt
{
	uint64_t bytes_done;
	uint64_t bytes_total;
	double seconds_elapsed;
	int error_code;
	Glib::ustring error_context;
};

class ImagingWorker_TQt : public TQThread
{
public:
	ImagingWorker_TQt( const Glib::ustring &src_path,
	                  const Glib::ustring &dst_path,
	                  uint64_t bytes_total,
	                  int src_is_blockdev,
	                  int dst_is_blockdev,
	                  int direction_restore,
	                  int opt_rescue_zerofill,
	                  int opt_sparse_zeros,
	                  int opt_sha256,
	                  int opt_sha256_verify );
	void run() override;
	void cancel();

	bool get_success();
	bool get_cancelled();
	void get_updates( std::vector<ImagingUpdate_TQt> &updates );

private:
	Glib::ustring m_src_path;
	Glib::ustring m_dst_path;
	uint64_t m_bytes_total;
	int m_src_is_blockdev;
	int m_dst_is_blockdev;
	int m_direction_restore;
	int m_opt_rescue_zerofill;
	int m_opt_sparse_zeros;
	int m_opt_sha256;
	int m_opt_sha256_verify;

	TQMutex m_state_mutex;
	int m_cancel_requested;
	int m_success;
	int m_cancelled;
	int m_fd_src;
	int m_fd_dst;
	int m_fd_src_buf;
	int m_fd_dst_buf;

	TQMutex m_queue_mutex;
	std::vector<ImagingUpdate_TQt> m_update_queue;
};

class Dialog_Imaging_Progress_TQt : public TQDialog
{
	TQ_OBJECT

public:
	Dialog_Imaging_Progress_TQt( const TQString &title, const TQString &op_label, TQWidget *parent );
	bool run_modal_imaging( ImagingWorker_TQt *worker );

private slots:
	void on_details_toggled( bool on );
	void on_cancel();
	void on_cancel_timeout();
	void on_pulse();
	void on_save();
	void on_ui_timeout();
	void on_worker_finished();

private:
	class ProgressWithText : public TQWidget
	{
	public:
		ProgressWithText( TQWidget *parent );
		void set_fraction( double f );
		void set_text( const TQString &t );
		void set_pulse_step( int step );
		void pulse();

		TQProgressBar *bar;
		TQLabel *label;
		int pulse_pos;
		int pulse_step;
	};

protected:
	void closeEvent( TQCloseEvent *e );
	void accept();

private:
	bool m_success;
	bool m_cancel;
	bool m_details_visible;
	bool m_running;
	bool m_force_cancel;
	uint64_t m_last_bytes;
	double m_last_secs;

	TQVBoxLayout *m_vbox;
	TQLabel *m_label_intro;
	TQLabel *m_label_current;
	ProgressWithText *m_progress_current;
	TQLabel *m_label_current_sub;
	TQLabel *m_label_completed;
	ProgressWithText *m_progress_all;
	TQPushButton *m_expander_button;
	TQWidget *m_details_container;
	TQListView *m_details_list;
	TQPushButton *m_btn_cancel;
	TQPushButton *m_btn_save;
	TQPushButton *m_btn_close;
	TQTimer *m_cancel_timer;
	TQTimer *m_pulse_timer;
	int m_cancel_countdown;
	int m_compact_height;
	TQString m_op_label;

	ImagingWorker_TQt *m_worker;
	TQTimer *m_ui_timer;
	TQPixmap m_icon_execute;
	TQPixmap m_icon_success;
	TQPixmap m_icon_error;
	TQPixmap m_icon_info;
	TQPixmap m_icon_warning;
};

}  // namespace GParted

#endif /* GPARTED_WIN_GPARTED_TQT_H */
