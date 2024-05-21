#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <boost/fusion/adapted.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <string>

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
    QmlParser() : QmlParser::base_type(element_rule) {
        using namespace qi;

        quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];
        unquoted_string %= lexeme[+(char_ - (char_("{") | char_("}") | char_(":") | char_(";") | qi::space))];
        property_rule %= unquoted_string >> ':' >> (quoted_string | unquoted_string) >> ';';
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

int main() {
    std::string input = 
    R"(
    ApplicationWindow {
        visible: true;
        width: 640;
        height: 480;
        title: "Nested QML Example";

        Rectangle {
            id: rect1;
            text: "Button 1";
            anchors.centerIn: parent;
            
                    Button {
                        id: button1;
                        text: "Button 1";
                        anchors.centerIn: parent;
                    }
        }
    }
    )";

    auto it = input.begin();
    auto end = input.end();
    qml::element root;
    QmlParser<decltype(it)> parser;

    if (qi::phrase_parse(it, end, parser, qi::space, root) && it == end) {
        std::cout << "Parse success\n";
        print_element(root);
    } else {
        std::cout << "Parse failed\n";
    }

    return 0;
}

