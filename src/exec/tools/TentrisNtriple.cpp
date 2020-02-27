#include <iostream>
#include <filesystem>

#include <tentris/store/RDF/SerdParser.hpp>
#include <tentris/store/TripleStore.hpp>
#include <tentris/util/All.hpp>

int main(int argc, char *argv[]) {
	using namespace rdf_parser::Turtle;
	using namespace tentris::store;
	using namespace fmt::literals;
	if (argc != 2) {
		std::cerr << "Please provide exactly one triple file as commandline argument." << std::endl;
		exit(EXIT_FAILURE);
	}

	TripleStore triple_store{};

	std::string rdf_file{argv[1]};
	if (not std::filesystem::is_regular_file(rdf_file)) {
		std::cerr << "{} is not a file."_format(rdf_file) << std::endl;
		exit(EXIT_FAILURE);
	}

	unsigned int total = 0;
	try {
		unsigned int count = 0;
		unsigned int _1mios = 0;
		for (const Triple &triple : rdf::SerdParser{rdf_file}) {

			triple_store.add(triple.subject(), triple.predicate(), triple.object());
			++count;
			++total;
			if (count == 1'000'000) {
				count = 0;
				++_1mios;
				std::cerr << "{:d} mio triples processed."_format(_1mios) << std::endl;
			}
		}
		std::cerr << "{:d} triples processed."_format(total) << std::endl;
	} catch (...) {
		throw std::invalid_argument{
				"A parsing error occurred while parsing {}. Error occured at {}th triple."_format(rdf_file, total)};
	}

	for (const auto &entry : triple_store.getBoolHypertrie()) {
		std::cout << entry[0]->getIdentifier() << " " << entry[1]->getIdentifier() << " " << entry[2]->getIdentifier()
		          << " .\n";
	}
}
