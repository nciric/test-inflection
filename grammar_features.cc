/*
 * clang++ -L/usr/local/lib -licuuc -licui18n -linflection -std=c++17 grammar_features.cc -o grammar_features
 * LD_LIBRARY_PATH=/usr/local/lib ./grammar_features
 *
 * Assuming that both inflection and icu4c are installed in /usr/local/lib
 */

#include <iostream>
#include <string>

#include <inflection/lang/features/LanguageGrammarFeatures.hpp>
#include <unicode/platform.h>
#include <unicode/uconfig.h>
#include <unicode/unistr.h>

using namespace icu;
using namespace std;

int main()
{
    inflection::util::ULocale locale("sr");
    string utf8;
    auto categories(inflection::lang::features::LanguageGrammarFeatures::getLanguageGrammarFeatures(locale).getCategories());
    for (const auto &[categoryName, category] : categories)
    {
        utf8.clear();
        UnicodeString name(categoryName);
        cout << name.toUTF8String<string>(utf8).c_str() << endl;
        for (const auto &value : category.getValues())
        {
            utf8.clear();
            UnicodeString value2(value);
            cout << "    " << value2.toUTF8String<string>(utf8).c_str() << endl;
        }
    }

    return 0;
}