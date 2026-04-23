AM_CPPFLAGS =						\
	-I$(top_srcdir)/include				\
	$(GTHREAD_CFLAGS) 				\
	$(GLIBMM_CFLAGS) 				\
	$(TQT_CFLAGS) 				\
	$(TDE_CFLAGS) 				\
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\"

AM_CFLAGS = -Wall	

AM_CXXFLAGS = -Wall	

AM_LDFLAGS =

libexec_PROGRAMS = tdepartedbin

BUILT_SOURCES = \
	tdeparted_icon_png.inc \
	tdeparted_about_png.inc \
	ssd_drive2_png.inc \
	nvme_drive2_png.inc \
	usb_drive2_png.inc \
	hard_drive2_png.inc \
	mount_png.inc \
	unmount_png.inc \
	new_png.inc \
	info_png.inc \
	pending_png.inc \
	resize_png.inc \
	sec_erase_png.inc \
	file_system_png.inc \
	flag_png.inc \
	label_png.inc \
	name_png.inc \
	delete_png.inc \
	bench_png.inc \
	quit_png.inc \
	smart_png.inc \
	device_png.inc \
	clone_png.inc \
	checkmark_png.inc \
	createtable_png.inc \
	mbrgpt_png.inc \
	moc_Win_GParted_TQt.cc

CLEANFILES = \
	$(BUILT_SOURCES)

tdepartedbin_SOURCES = \
  BCache_Info.cc			\
  BlockSpecial.cc			\
  CopyBlocks.cc			\
  DMRaid.cc			\
  Device.cc			\
  FS_Info.cc			\
  FileSystem.cc			\
  GParted_Core.cc			\
  LVM2_PV_Info.cc			\
  LUKS_Info.cc			\
  Mount_Info.cc			\
  Operation.cc			\
  OperationChangeUUID.cc		\
  OperationCheck.cc		\
  OperationCopy.cc		\
  OperationCreate.cc		\
  OperationDelete.cc		\
  OperationDetail.cc		\
  OperationFormat.cc		\
  OperationLabelFileSystem.cc	\
  OperationNamePartition.cc	\
  OperationCreatePartitionTable.cc	\
  OperationConvertPartitionTable.cc	\
  OperationResizeMove.cc		\
  Partition.cc			\
  PartitionLUKS.cc		\
  PartitionVector.cc		\
  PasswordRAMStore.cc		\
  PipeCapture.cc			\
  Proc_Partitions_Info.cc		\
  ProgressBar.cc			\
  SupportedFileSystems.cc		\
  SWRaid_Info.cc			\
  Utils.cc			\
  bcachefs.cc			\
  btrfs.cc			\
  exfat.cc			\
  ext2.cc				\
  f2fs.cc				\
  fat16.cc			\
  hfs.cc				\
  hfsplus.cc			\
  jfs.cc				\
  linux_swap.cc			\
  lvm2_pv.cc			\
  luks.cc				\
  main_tqt3.cc			\
  Win_GParted_TQt.cc		\
  moc_Win_GParted_TQt.cc		\
  minix.cc			\
  nilfs2.cc			\
  ntfs.cc				\
  reiser4.cc			\
  reiserfs.cc			\
  udf.cc				\
  xfs.cc

tdepartedbin_LDADD = $(GTHREAD_LIBS) $(GLIBMM_LIBS) $(TQT_LIBS) $(TDE_LIBS)

moc_Win_GParted_TQt.cc: $(top_srcdir)/include/Win_GParted_TQt.h
	moc-tqt tqmoc $< $@

tdeparted_icon_png.inc: $(top_srcdir)/icons/tdeparted_icon.png
	xxd -i -n tdeparted_icon_png $< > $@

tdeparted_about_png.inc: $(top_srcdir)/icons/tdeparted_about.png
	xxd -i -n tdeparted_about_png $< > $@

ssd_drive2_png.inc: $(top_srcdir)/icons/ssd-drive2.png
	xxd -i -n ___ssd_drive2_png $< > $@

nvme_drive2_png.inc: $(top_srcdir)/icons/nvme-drive2.png
	xxd -i -n ___nvme_drive2_png $< > $@

usb_drive2_png.inc: $(top_srcdir)/icons/usb-drive2.png
	xxd -i -n ___usb_drive2_png $< > $@

hard_drive2_png.inc: $(top_srcdir)/icons/hard-drive2.png
	xxd -i -n ___hard_drive2_png $< > $@

mount_png.inc: $(top_srcdir)/icons/mount.png
	xxd -i -n ___mount_png $< > $@

unmount_png.inc: $(top_srcdir)/icons/unmount.png
	xxd -i -n ___unmount_png $< > $@

new_png.inc: $(top_srcdir)/icons/new.png
	xxd -i -n ___new_png $< > $@

info_png.inc: $(top_srcdir)/icons/info.png
	xxd -i -n ___info_png $< > $@

pending_png.inc: $(top_srcdir)/icons/pending.png
	xxd -i -n ___pending_png $< > $@

resize_png.inc: $(top_srcdir)/icons/resize.png
	xxd -i -n ___resize_png $< > $@

sec_erase_png.inc: $(top_srcdir)/icons/sec_erase.png
	xxd -i -n ___sec_erase_png $< > $@

file_system_png.inc: $(top_srcdir)/icons/file-system.png
	xxd -i -n ___file_system_png $< > $@

flag_png.inc: $(top_srcdir)/icons/flag.png
	xxd -i -n ___flag_png $< > $@

label_png.inc: $(top_srcdir)/icons/label.png
	xxd -i -n ___label_png $< > $@

name_png.inc: $(top_srcdir)/icons/name.png
	xxd -i -n ___name_png $< > $@

delete_png.inc: $(top_srcdir)/icons/delete.png
	xxd -i -n ___delete_png $< > $@

bench_png.inc: $(top_srcdir)/icons/bench.png
	xxd -i -n ___bench_png $< > $@

quit_png.inc: $(top_srcdir)/icons/quit.png
	xxd -i -n ___quit_png $< > $@

smart_png.inc: $(top_srcdir)/icons/smart.png
	xxd -i -n ___smart_png $< > $@

device_png.inc: $(top_srcdir)/icons/device.png
	xxd -i -n ___device_png $< > $@

clone_png.inc: $(top_srcdir)/icons/clone.png
	xxd -i -n ___clone_png $< > $@

checkmark_png.inc: $(top_srcdir)/icons/checkmark.png
	xxd -i -n ___checkmark_png $< > $@

createtable_png.inc: $(top_srcdir)/icons/createtable.png
	xxd -i -n ___createtable_png $< > $@

mbrgpt_png.inc: $(top_srcdir)/icons/mbrgpt.png
	xxd -i -n ___mbrgpt_png $< > $@

all-local: tdepartedbin
	@if test "x$(RELEASE)" = "x1"; then \
		if command -v sstrip >/dev/null 2>&1; then \
			if test -f ./tdepartedbin; then \
				sstrip ./tdepartedbin || exit $$?; \
			fi; \
		fi; \
	fi

if RELEASE_BUILD
AM_CXXFLAGS += -Os -g0 -flto=auto -fuse-linker-plugin -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables -fmerge-all-constants -fno-ident -fomit-frame-pointer -fno-stack-protector -fvisibility=hidden -fno-plt
AM_LDFLAGS += -Wl,--gc-sections -Wl,--strip-all -Wl,-z,norelro -Wl,--as-needed -Wl,-z,combreloc -Wl,--build-id=none
endif
