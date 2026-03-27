#ifndef MYTABLEMODEL_H_

#define MYTABLEMODEL_H_

#include <QAbstractTableModel>
#include <QAbstractItemView>
#include "service.h"
#include <vector>
#include "domain.h"

using std::vector;

class MyTableModel : public QAbstractTableModel {
private:
	vector<Medicament> medicamente;

public:
	MyTableModel(const vector<Medicament>& meds) : medicamente{ meds } {

	}

	int rowCount(const QModelIndex& = QModelIndex()) const override {
		return (int)medicamente.size();
	}

	int columnCount(const QModelIndex& = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Medicament medicament = medicamente[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(medicament.getDenumire());
			}
			if (index.column() == 1) {
				return QString::number(medicament.getPret());
			}
			if (index.column() == 2) {
				return QString::fromStdString(medicament.getProducator());
			}
			if (index.column() == 3) {
				return QString::fromStdString(medicament.getSubstantaActiva());
			}
		}
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const {
		if (orientation == Qt::Horizontal) {
			if (role == Qt::DisplayRole) {
				switch (section) {
				case 0:
					return "Denumire";
					break;
				case 1:
					return "Pret";
					break;
				case 2:
					return "Producator";
					break;
				case 3:
					return "Substanta activa";
					break;
				default:
					return QString("Column %1").arg(section + 1);
					break;
				}
			}
		}
		else if (orientation == Qt::Vertical) {
			if (role == Qt::DisplayRole) {
				return section + 1;
			}
		}
		return QVariant();
	}

	Medicament getMedicament(const QModelIndex& index) {
		return medicamente[index.row()];
	}

	void setMedicamente(const vector<Medicament>& medicament) {
		this->medicamente = medicament;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
		emit layoutChanged();
	}
};



#endif // !MYTABLEMODEL_H_

