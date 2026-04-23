/* Copyright (C) 2026
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 */

#include "OperationConvertPartitionTable.h"

#include "GParted_Core.h"
#include "Partition.h"

namespace GParted
{

OperationConvertPartitionTable::OperationConvertPartitionTable( const Device &device, const Glib::ustring &from, const Glib::ustring &to )
: Operation( OPERATION_CONVERT_PARTITION_TABLE, device,
             [] (const Device &d) {
		     Partition p;
		     p.set_unpartitioned( d.get_path(), "", FS_UNALLOCATED, d.length, d.sector_size, false );
		     return p;
     }( device ),
             [] (const Device &d) {
		     Partition p;
		     p.set_unpartitioned( d.get_path(), "", FS_UNALLOCATED, d.length, d.sector_size, false );
		     return p;
     }( device ) ),
  m_from( from ),
  m_to( to )
{
	create_description();
}

void OperationConvertPartitionTable::apply_to_visual( PartitionVector &partitions )
{
	// Visual layout remains as-is until Apply; after conversion the disk is rescanned.
	(void)partitions;
}

void OperationConvertPartitionTable::create_description()
{
	m_description = Glib::ustring::compose( _( "Convert partition table on %1 from %2 to %3" ), m_device.get_path(), m_from, m_to );
}

bool OperationConvertPartitionTable::merge_operations( const Operation &candidate )
{
	if (candidate.m_type != OPERATION_CONVERT_PARTITION_TABLE)
		return false;
	if (candidate.m_device.get_path() != m_device.get_path())
		return false;
	const OperationConvertPartitionTable *o = dynamic_cast<const OperationConvertPartitionTable *>( &candidate );
	if (!o)
		return false;
	m_from = o->m_from;
	m_to = o->m_to;
	create_description();
	return true;
}

}  // namespace GParted
