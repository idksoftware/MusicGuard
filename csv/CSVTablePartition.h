#pragma once

#include "MetaType.h"
namespace simplearchive {
	class CSVTablePartition : public MTTable
	{
	public:
		CSVTablePartition(MTTableSchema* pSchemaTable) : MTTable(pSchemaTable) {};
		virtual ~CSVTablePartition() = default;
		virtual bool save(const char* rootPath, MTRow& row) {
			return true;
		};
		virtual bool updateRow(const char* rootPath, MTRow& row, size_t idx, const char* value)
		{
			return true;
		}
		virtual bool findRow(SharedMTRow &row, size_t idx, const char* value)
		{
			for (auto i = this->begin(); i != this->end(); i++) {
				MTColumn& col = (*i)->columnAt(idx);
				if (col.toString() == value)
				{
					row = *i;
					return true;
				}
			}
			return false;
		}

		virtual bool findRow(SharedMTRow& row, size_t idx)
		{
			MTColumn& col1 = row->columnAt(idx);

			for (auto i = this->begin(); i != this->end(); i++) {
				MTColumn& col2 = (*i)->columnAt(idx);
				if (col1 == col2)
				{
					row = *i;
					return true;
				}
			}
			return false;
		}
	};

};