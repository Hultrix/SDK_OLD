#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <boost/fusion/adapted.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <string>

// Define CSS-related types and data within a dedicated namespace.
namespace css {
    // Enumeration for different text alignment options within CSS.
    enum class text_align : std::uint8_t { left, right, center, justify };
    
    // Enumeration for align-items property.
    // enum class align_items : std::uint8_t { flex_start, flex_end, center, baseline, stretch }; // align-items
}

// Short namespace aliases for Boost libraries used in the parser.
namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;
namespace spirit = boost::spirit;

// Template for mapping string values to enum values for CSS properties.
template <typename T>
struct enum_map;

// Specialization of enum_map for the text_align enum.
template <>
struct enum_map<css::text_align> {
    static const std::unordered_map<std::string, css::text_align>& values() {
        static const std::unordered_map<std::string, css::text_align> v = {
            {"left", css::text_align::left},
            {"right", css::text_align::right},
            {"center", css::text_align::center},
            {"justify", css::text_align::justify}
        };
        return v;
    }
};

// Specialization of enum_map for the align_items enum.
// align-items
/*
template <>
struct enum_map<css::align_items> {
    static const std::unordered_map<std::string, css::align_items>& values() {
        static const std::unordered_map<std::string, css::align_items> v = {
            {"flex-start", css::align_items::flex_start},
            {"flex-end", css::align_items::flex_end},
            {"center", css::align_items::center},
            {"baseline", css::align_items::baseline},
            {"stretch", css::align_items::stretch}
        };
        return v;
    }
};
*/

// Parser component that uses enum_map to convert string tokens to enum values.
template <typename T>
struct enum_parser : qi::symbols<char, T> {
    enum_parser() {
        for (const auto& kv : enum_map<T>::values()) {
            this->add(kv.first, kv.second); // Add each string-enum pair to the parser.
        }
    }
};

// Structures to hold CSS declarations.
struct declaration_block {
    boost::optional<css::text_align> text_align; // Enum value for CSS text-align property.
    boost::optional<std::string> color;          // CSS color value as a string.
    // boost::optional<std::string> margin;         // CSS margin value as a string.
    // boost::optional<css::align_items> align_items; // Enum value for CSS align-items property.
};

struct css_rule {
    std::string selector;       // CSS selector.
    declaration_block block;    // Block of declarations for this selector.
};

// Adapt the CSS structures to work with Boost.Fusion.
BOOST_FUSION_ADAPT_STRUCT(
    declaration_block,
    text_align,
    color
    // margin,
    // align_items
)

BOOST_FUSION_ADAPT_STRUCT(
    css_rule,
    selector,
    block
)

// Grammar definition for parsing CSS.
template <typename Iterator>
class StyleParser : public qi::grammar<Iterator, std::vector<css_rule>(), qi::space_type> {
public:
    StyleParser() : StyleParser::base_type(start) {
        // Define how a CSS selector is parsed (now just tag names).
        selector_rule = qi::lexeme[+(qi::alnum | qi::char_('-'))]; // Parses alphanumeric strings and hyphens.
        
        // Define how a text-align property is parsed.
        text_align_rule = qi::lit("text-align") >> ':' >> enum_text_align >> ';';
        
        // Define how a color property is parsed.
        color_rule = qi::lit("color") >> ':' >> qi::lexeme[+(qi::char_ - ';')] >> ';';
        
        // Define how a margin property is parsed.
        // margin_rule = qi::lit("margin") >> ':' >> qi::lexeme[+(qi::char_ - ';')] >> ';';
        
        // Define how an align-items property is parsed.
        // align_items_rule = qi::lit("align-items") >> ':' >> enum_align_items >> ';';
        
        // Rule to parse a block of declarations.
        declaration_block_rule = -text_align_rule >> -color_rule; // >> -margin_rule >> -align_items_rule;
        
        // Rule to parse a full CSS rule consisting of a selector and a declaration block.
        rule = selector_rule >> '{' >> declaration_block_rule >> '}';
        
        // The starting point for parsing that expects one or more CSS rules.
        start = +rule;
    }

private:
    enum_parser<css::text_align> enum_text_align; // Parser for text-align property.
    // enum_parser<css::align_items> enum_align_items; // Parser for align-items property.
    qi::rule<Iterator, std::string(), qi::space_type> selector_rule; // Parser for CSS selector.
    qi::rule<Iterator, css::text_align(), qi::space_type> text_align_rule; // Parser for text-align property.
    qi::rule<Iterator, std::string(), qi::space_type> color_rule; // Parser for color property.
    // qi::rule<Iterator, std::string(), qi::space_type> margin_rule; // Parser for margin property.
    // qi::rule<Iterator, css::align_items(), qi::space_type> align_items_rule; // Parser for align-items property.
    qi::rule<Iterator, declaration_block(), qi::space_type> declaration_block_rule; // Parser for declaration block.
    qi::rule<Iterator, css_rule(), qi::space_type> rule; // Parser for individual CSS rule.
    qi::rule<Iterator, std::vector<css_rule>(), qi::space_type> start; // Starting rule for parser.
};

int main() {
    std::string input = 
    R"(
    button1 {
        text-align: left;
        color: red;
    }
    )";

    auto it = input.begin(); // Iterator to the beginning of the input string.
    auto end = input.end(); // Iterator to the end of the input string.
    std::vector<css_rule> rules; // Vector to store parsed CSS rules.
    StyleParser<decltype(it)> parser; // Instantiate the parser with the type of iterator.

    // Parse the input using the defined parser and check for complete parsing.
    if (qi::phrase_parse(it, end, parser, qi::space, rules) && it == end) {
        std::cout << "Parse success\n";
        // Output the results of parsing.
        for (const auto& rule : rules) {
            std::cout << "selector: " << rule.selector << "\n";
            if (rule.block.text_align) {
                std::cout << "text-align: " << static_cast<int>(*rule.block.text_align) << "\n";
            }
            if (rule.block.color) {
                std::cout << "color: " << *rule.block.color << "\n";
            }
            // if (rule.block.margin) {
            //     std::cout << "margin: " << *rule.block.margin << "\n";
            // }
            // if (rule.block.align_items) {
            //     std::cout << "align-items: " << static_cast<int>(*rule.block.align_items) << "\n";
            // }
        }
    } else {
        std::cout << "Parse failed\n"; // Indicate parse failure.
    }
    return 0; // Return success status.
}

