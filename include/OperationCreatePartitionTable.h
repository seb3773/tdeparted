/* Copyright (C) 2026
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 */

#ifndef GPARTED_OPERATION_CREATE_PARTITION_TABLE_H
#define GPARTED_OPERATION_CREATE_PARTITION_TABLE_H

#include "Operation.h"

namespace GParted
{

class OperationCreatePartitionTable : public Operation
{
public:
	OperationCreatePartitionTable( const Device &device, const Glib::ustring &new_disklabel );

	void apply_to_visual( PartitionVector &partitions ) override;
	void create_description() override;
	bool merge_operations( const Operation &candidate ) override;

	const Glib::ustring &get_new_disklabel() const { return m_new_disklabel; }

private:
	Glib::ustring m_new_disklabel;
};

}  // namespace GParted

#endif /* GPARTED_OPERATION_CREATE_PARTITION_TABLE_H */
