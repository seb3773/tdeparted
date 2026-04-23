/* Copyright (C) 2026
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 */

#include "OperationCreatePartitionTable.h"

#include "GParted_Core.h"
#include "Partition.h"
#include "Utils.h"

namespace GParted
{

OperationCreatePartitionTable::OperationCreatePartitionTable( const Device &device, const Glib::ustring &new_disklabel )
: Operation( OPERATION_CREATE_PARTITION_TABLE, device,
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
  m_new_disklabel( new_disklabel )
{
	create_description();
}

void OperationCreatePartitionTable::apply_to_visual( PartitionVector &partitions )
{
	partitions.clear();
	GParted_Core::insert_unallocated( m_device.get_path(), partitions, 0, m_device.length - 1, m_device.sector_size, false );
}

void OperationCreatePartitionTable::create_description()
{
	m_description = Glib::ustring::compose( _( "Create partition table %1 on %2" ), m_new_disklabel, m_device.get_path() );
}

bool OperationCreatePartitionTable::merge_operations( const Operation &candidate )
{
	if (candidate.m_type != OPERATION_CREATE_PARTITION_TABLE)
		return false;
	if (candidate.m_device.get_path() != m_device.get_path())
		return false;
	const OperationCreatePartitionTable *o = dynamic_cast<const OperationCreatePartitionTable *>( &candidate );
	if (!o)
		return false;
	m_new_disklabel = o->m_new_disklabel;
	create_description();
	return true;
}

}  // namespace GParted
