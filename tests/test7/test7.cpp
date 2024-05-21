#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <boost/fusion/adapted.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>

namespace qml {
    struct property {
        std::string name;
        std::string value;
    };

    struct element {
        std::string type;
        std::vector<property> properties;
        std::vector<element> children;
    };
}

BOOST_FUSION_ADAPT_STRUCT(qml::property, name, value)
BOOST_FUSION_ADAPT_STRUCT(qml::element, type, properties, children)

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

template <typename Iterator>
struct QmlParser : qi::grammar<Iterator, qml::element(), qi::space_type> {
    QmlParser() : QmlParser::base_type(start) {
        using namespace qi;

        quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];
        unquoted_string %= lexeme[+(char_ - (char_("{") | char_("}") | char_(":") | char_(";") | qi::space))];
        property_rule %= unquoted_string >> ':' >> (quoted_string | unquoted_string);
        properties_rule %= *property_rule;

        element_rule %= 
            unquoted_string >> '{' >> properties_rule >> *element_rule >> '}';

        start = element_rule;
    }

    qi::rule<Iterator, std::string(), qi::space_type> quoted_string;
    qi::rule<Iterator, std::string(), qi::space_type> unquoted_string;
    qi::rule<Iterator, qml::property(), qi::space_type> property_rule;
    qi::rule<Iterator, std::vector<qml::property>(), qi::space_type> properties_rule;
    qi::rule<Iterator, qml::element(), qi::space_type> element_rule;
    qi::rule<Iterator, qml::element(), qi::space_type> start;
};

void print_element(const qml::element& el, int indent = 0) {
    std::string indentation(indent, ' ');
    std::cout << indentation << "Element type: " << el.type << "\n";
    for (const auto& prop : el.properties) {
        std::cout << indentation << "  Property: " << prop.name << " = " << prop.value << "\n";
    }
    for (const auto& child : el.children) {
        print_element(child, indent + 2);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    auto it = input.begin();
    auto end = input.end();
    qml::element root;
    QmlParser<decltype(it)> parser;

    bool r = qi::phrase_parse(it, end, parser, qi::space, root);

    if (r && it == end) {
        std::cout << "Parse success\n";
        print_element(root);
    } else {
        std::cout << "Parse failed\n";
        std::cout << "Remaining unparsed: '" << std::string(it, end) << "'\n";
    }

    return 0;
}

