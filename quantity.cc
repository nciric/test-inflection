/*
 * clang++ -L/usr/local/lib -licuuc -licui18n -linflection -std=c++20 grammar_features.cc -o grammar_features
 * LD_LIBRARY_PATH=/usr/local/lib ./grammar_features
 *
 * Assuming that both inflection and icu4c are installed in /usr/local/lib
 */

#include <inflection/dialog/CommonConceptFactory.hpp>
#include <inflection/dialog/InflectableStringConcept.hpp>
#include <inflection/dialog/LocalizedCommonConceptFactoryProvider.hpp>
#include <inflection/dialog/NumberConcept.hpp>
#include <inflection/dialog/SemanticFeatureModel.hpp>
#include <inflection/dialog/SpeakableString.hpp>
#include <unicode/unistr.h>
#include <iostream>
#include <memory>

using namespace icu;
using namespace inflection::dialog;
using namespace inflection::util;
using namespace std;

int main(const int argc, const char* const argv[])
{
    ULocale serbian("sr");
    const auto conceptFactory = LocalizedCommonConceptFactoryProvider::getDefaultCommonConceptFactoryProvider()->getCommonConceptFactory(serbian);

    InflectableStringConcept message(conceptFactory->getSemanticFeatureModel(), SpeakableString(u"девојка"));
    NumberConcept one(static_cast<int64_t>(1), serbian, serbian);
    unique_ptr<SpeakableString> result(conceptFactory->quantify(one, &message));
    if (result != nullptr) {
        string print;
        string speak;
        UnicodeString::readOnlyAlias(result->getPrint()).toUTF8String(print);
        UnicodeString::readOnlyAlias(result->getSpeak()).toUTF8String(speak);
        cout << "print: " << print << endl;
        cout << "speak: " << speak << endl;
    }

    NumberConcept two(static_cast<int64_t>(2), serbian, serbian);
    result.reset(conceptFactory->quantify(two, &message));
    if (result != nullptr) {
        string print;
        string speak;
        UnicodeString::readOnlyAlias(result->getPrint()).toUTF8String(print);
        UnicodeString::readOnlyAlias(result->getSpeak()).toUTF8String(speak);
        cout << "print: " << print << endl;
        cout << "speak: " << speak << endl;
    }

    // Change the grammatical case of the number and noun.
    message.putConstraintByName(u"case", u"dative");
    result.reset(conceptFactory->quantify(one, &message));
    if (result != nullptr) {
        string print;
        string speak;
        UnicodeString::readOnlyAlias(result->getPrint()).toUTF8String(print);
        UnicodeString::readOnlyAlias(result->getSpeak()).toUTF8String(speak);
        cout << "print: " << print << endl;
        cout << "speak: " << speak << endl;
    }
}