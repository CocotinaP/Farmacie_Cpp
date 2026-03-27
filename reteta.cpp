#include "reteta.h"
#include <random>
#include "exceptii.h"
#include <fstream>

using std::ofstream;

Reteta::Reteta() {
	reteta.clear();
}

void Reteta::adaugaMedicamentInReteta(const Medicament& medicament) {
	reteta.push_back(medicament);
	notify();
}

void Reteta::adaugaRandom(const vector<Medicament>& medicamente, int nr) {
	if (nr > medicamente.size()) {
		throw(RetetaExceptii("Medicamente insuficiente!\n"));
	}
	else {
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, (int)medicamente.size() - 1);
		int randNr;
		for (int i = 0; i < nr; i++) {
			randNr = dist(mt);
			adaugaMedicamentInReteta(medicamente[randNr]);
		}
	}
	notify();
}

vector<Medicament> Reteta::getReteta() {
	return reteta;
}

void Reteta::golesteReteta() noexcept{
	reteta.clear();
	notify();
}

void Reteta::exportHTML(const string& fileName) {
	string fileHTML = fileName;
	const auto pos = fileHTML.find_last_of(".");
	if (pos < fileHTML.size()) {
		auto fileExtension = fileName.substr(pos);
		if (fileExtension != ".html") {
			fileHTML += ".html";
		}
	}
	else {
		fileHTML += ".html";
	}

	ofstream htmlFile(fileHTML);
	htmlFile << "<html>\n"
		"<head>\n"
		"<title>Reteta</title>\n"
		"<h1><div align=\"center\"><b>Reteta</b></div></h1>\n"
		"	</head>\n"
		"<style>\n"
		"table, th, td {\n"
			"border:1px solid white;\n"
			"border-collapse: collapse;\n"
			"border-radius: 10px\n"
		"}\n"
		"tr:hover {background-color: #FFB6C1;}\n"
		"</style>\n"
		"<body>\n";
		htmlFile << "<table style=\"width:100%\">\n"
			"<tr>\n"
			"	<th><b><font color=#CC0099>ID</font></b></th>\n"
			"	<th><b><font color=#CC0099>Denumire</font></b></th>\n"
			"	<th><b><font color=#CC0099>Pret</font></b></th>\n"
			"	<th><b><font color=#CC0099>Producator</font></b></th>\n"
			"	<th><b><font color=#CC0099>Substanta activa</font></b></th>\n"
			"<tr>\n";
		for (const auto& m : getReteta()) {
			htmlFile << "<tr>\n";
			htmlFile << "<td><b>" << m.getId() << "</b></td>\n";
			htmlFile << "<td><b>" << m.getDenumire() << "</b></td>\n";
			htmlFile << "<td><b>" << m.getPret() << "</b></td>\n";
			htmlFile << "<td><b>" << m.getProducator() << "</b></td>\n";
			htmlFile << "<td><b>" << m.getSubstantaActiva() << "</b></td>\n";
			htmlFile << "</tr>\n";
		}
		htmlFile << "</table>\n"
			"\n"
			"\n"
			"</body>\n"
			"</html>\n";
}