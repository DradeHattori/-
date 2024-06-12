#include "ini.h"

using namespace std;

namespace ini {

    // реализация методов должна быть в файле ini.cpp
    Section& Document::AddSection(std::string name) {
        return sections_[name];
    }
    const Section& Document::GetSection(const std::string& name) const {
        return sections_.at(name);
    }

    std::size_t Document::GetSectionCount() const {
        return sections_.size();
    }



    // определение этой функции должно быть в файле ini.cpp
    Document Load(std::istream& input) {
        Document loaded_doc;
        Section* section = new Section;

        string input_data;

        while (getline(input, input_data)) {

            if (input_data.empty() || input_data[0] == ';') {
                continue;
            }

            if (input_data[0] == '[') {
                auto start_section_It = input_data.find_first_of('[') + 1;
                auto end_section_It = input_data.find_first_of(']') - 1;
                input_data = input_data.substr(start_section_It, end_section_It);

                section = &loaded_doc.AddSection(input_data);
                
            }
            else {
                auto equal_sign_It = input_data.find_first_of('=');
                string section_name = input_data.substr(0, equal_sign_It);
                string section_value = input_data.substr(equal_sign_It + 1);

                section->insert({ section_name, section_value });
            }

        }
        return loaded_doc;
    }

}
