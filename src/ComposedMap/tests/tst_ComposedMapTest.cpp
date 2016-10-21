#include <QtTest>
#include "../composedmap.h"

class ComposedMapTest : public QObject
{
    Q_OBJECT

    public:
        ComposedMapTest();

    private Q_SLOTS:
        void beginTest();
        void endTest();
        void cbeginTest();
        void cendTest();
        void mbeginTest();
        void mendTest();
        void emptyTest();
        void elementsCountTest();
        void clearTest();
        void eraseTest();

    private:
        ComposedMap<int, std::vector<std::string>> emptyVect;
        const ComposedMap<int, std::vector<std::string>> constEmptyVect;

        ComposedMap<int, std::vector<std::string>> pseudoEmptyVect;
        const ComposedMap<int, std::vector<std::string>> constPseudoEmptyVect;

        ComposedMap<int, std::vector<std::string>> vect;
        const ComposedMap<int, std::vector<std::string>> constVect;


        ComposedMap<int, std::map<char, std::string>> emptyMap;
        const ComposedMap<int, std::map<char, std::string>> constEmptyMap;

        ComposedMap<int, std::map<char, std::string>> pseudoEmptyMap;
        const ComposedMap<int, std::map<char, std::string>> constPseudoEmptyMap;

        ComposedMap<int, std::map<char, std::string>> map;
        const ComposedMap<int, std::map<char, std::string>> constMap;


        ComposedMap<int, std::vector<std::string>>::iterator evit;
        ComposedMap<int, std::vector<std::string>>::const_iterator evcit;

        ComposedMap<int, std::vector<std::string>>::iterator pevit;
        ComposedMap<int, std::vector<std::string>>::const_iterator pevcit;

        ComposedMap<int, std::vector<std::string>>::iterator vit;
        ComposedMap<int, std::vector<std::string>>::const_iterator vcit;

        ComposedMap<int, std::map<char, std::string>>::iterator epmit;
        ComposedMap<int, std::map<char, std::string>>::const_iterator emcit;

        ComposedMap<int, std::map<char, std::string>>::iterator pemit;
        ComposedMap<int, std::map<char, std::string>>::const_iterator pemcit;

        ComposedMap<int, std::map<char, std::string>>::iterator mit;
        ComposedMap<int, std::map<char, std::string>>::const_iterator mcit;



        ComposedMap<int, std::vector<std::string>> createPseudoEmptyVect();
        ComposedMap<int, std::map<char, std::string>> createPseudoEmptyMap();
        ComposedMap<int, std::vector<std::string>> createVectComposedMap();
        ComposedMap<int, std::map<char, std::string>> createMapComposedMap();

};

ComposedMapTest::ComposedMapTest()
    : pseudoEmptyVect(createPseudoEmptyVect()), constPseudoEmptyVect(createPseudoEmptyVect()),
        vect(createVectComposedMap()), constVect(createVectComposedMap()),
        pseudoEmptyMap(createPseudoEmptyMap()), constPseudoEmptyMap(createPseudoEmptyMap()),
        map(createMapComposedMap()), constMap(createMapComposedMap()),
        evit(emptyVect), evcit(constEmptyVect), pevit(pseudoEmptyVect), pevcit(constPseudoEmptyVect),
        vit(vect), vcit(constVect), epmit(emptyMap), emcit(constEmptyMap), pemit(pseudoEmptyMap),
        pemcit(constPseudoEmptyMap), mit(map), mcit(constMap)
{

}

ComposedMap<int, std::vector<std::string>> ComposedMapTest::createPseudoEmptyVect()
{
    ComposedMap<int, std::vector<std::string>> vects;
    vects[1];
    return vects;
}

ComposedMap<int, std::map<char, std::string>> ComposedMapTest::createPseudoEmptyMap()
{
    ComposedMap<int, std::map<char, std::string>> map;
    map[2];
    return map;
}

ComposedMap<int, std::vector<std::string>> ComposedMapTest::createVectComposedMap()
{
    ComposedMap<int, std::vector<std::string>> vects;
    std::vector<std::string> subVect1 {"1", "2", "3"};
    std::vector<std::string> subVect2 {"4"};
    std::vector<std::string> subVect3 {"5", "6"};

    vects[1] = subVect1;
    vects[2] = subVect2;
    vects[3] = subVect3;

    return vects;
}

ComposedMap<int, std::map<char, std::string>> ComposedMapTest::createMapComposedMap()
{
    ComposedMap<int, std::map<char, std::string>> maps;
    std::map<char, std::string> subMap1 {{'a', "1"}, {'b', "2"}, {'c', "3"}};
    std::map<char, std::string> subMap2 {{'d', "4"}};
    std::map<char, std::string> subMap3 {{'e', "5"}, {'f', "6"}};

    maps[1] = subMap1;
    maps[2] = subMap2;
    maps[3] = subMap3;

    return maps;
}

void ComposedMapTest::beginTest()
{
    evit = emptyVect.begin();
    QCOMPARE(evit, emptyVect.end());
    evcit = constEmptyVect.begin();
    QCOMPARE(evcit, constEmptyVect.end());

    pevit = pseudoEmptyVect.begin();
    QCOMPARE(pevit, pseudoEmptyVect.end());
    pevcit = constPseudoEmptyVect.begin();
    QCOMPARE(pevcit, constPseudoEmptyVect.end());

    vit = vect.begin();
    QVERIFY(vit != vect.end() && *vit == "1");
    vcit = constVect.begin();
    QVERIFY(vcit != constVect.end() && *vcit == "1");


    epmit = emptyMap.begin();
    QCOMPARE(epmit, emptyMap.end());
    emcit = constEmptyMap.begin();
    QCOMPARE(emcit, constEmptyMap.end());

    pemit = pseudoEmptyMap.begin();
    QCOMPARE(pemit, pseudoEmptyMap.end());
    pemcit = constPseudoEmptyMap.begin();
    QCOMPARE(pemcit, constPseudoEmptyMap.end());

    mit = map.begin();
    QVERIFY(mit != map.end() && *mit == "1");
    mcit = constMap.begin();
    QVERIFY(mcit != constMap.end() && *mcit == "1");
}

void ComposedMapTest::endTest()
{
    evit = emptyVect.end();
    evit--;
    QCOMPARE(evit, emptyVect.end());
    evcit = constEmptyVect.end();
    evcit--;
    QCOMPARE(evcit, constEmptyVect.end());

    pevit = pseudoEmptyVect.end();
    pevit--;
    QCOMPARE(pevit, pseudoEmptyVect.end());
    pevcit = constPseudoEmptyVect.end();
    pevcit--;
    QCOMPARE(pevcit, constPseudoEmptyVect.end());

    vit = vect.end();
    vit--;
    QVERIFY(vit != vect.end() && *vit == "6");
    vcit = constVect.end();
    vcit--;
    QVERIFY(vcit != constVect.end() && *vcit == "6");


    epmit = emptyMap.end();
    epmit--;
    QCOMPARE(epmit, emptyMap.end());
    emcit = constEmptyMap.end();
    emcit--;
    QCOMPARE(emcit, constEmptyMap.end());

    pemit = pseudoEmptyMap.end();
    pemit--;
    QCOMPARE(pemit, pseudoEmptyMap.end());
    pemcit = constPseudoEmptyMap.end();
    pemcit--;
    QCOMPARE(pemcit, constPseudoEmptyMap.end());

    mit = map.end();
    mit--;
    QVERIFY(mit != map.end() && *mit == "6");
    mcit = constMap.end();
    mcit--;
    QVERIFY(mcit != constMap.end() && *mcit == "6");
}

void ComposedMapTest::cbeginTest()
{
    QCOMPARE(constEmptyVect.cbegin(), constEmptyVect.begin());
    QCOMPARE(constPseudoEmptyVect.cbegin(), constPseudoEmptyVect.begin());
    QCOMPARE(constVect.cbegin(), constVect.begin());

    QCOMPARE(constEmptyMap.cbegin(), constEmptyMap.begin());
    QCOMPARE(constPseudoEmptyMap.cbegin(), constPseudoEmptyMap.begin());
    QCOMPARE(constMap.cbegin(), constMap.begin());
}

void ComposedMapTest::cendTest()
{
    QCOMPARE(constEmptyVect.cend(), constEmptyVect.end());
    QCOMPARE(constPseudoEmptyVect.cend(), constPseudoEmptyVect.end());
    QCOMPARE(constVect.cend(), constVect.end());

    QCOMPARE(constEmptyMap.cend(), constEmptyMap.end());
    QCOMPARE(constPseudoEmptyMap.cend(), constPseudoEmptyMap.end());
    QCOMPARE(constMap.cend(), constMap.end());
}

void ComposedMapTest::mbeginTest()
{
    QCOMPARE(emptyVect.mbegin(), emptyVect.mend());
    QCOMPARE(constEmptyVect.mbegin(), constEmptyVect.mend());

    auto vit = pseudoEmptyVect.mbegin();
    QCOMPARE(vit->first, 1);
    ++vit;
    QCOMPARE(vit, pseudoEmptyVect.mend());
    auto cvit = constPseudoEmptyVect.mbegin();
    QCOMPARE(cvit->first, 1);
    ++cvit;
    QCOMPARE(cvit, constPseudoEmptyVect.mend());

    QCOMPARE(vect.mbegin()->first, 1);
    QCOMPARE(constVect.mbegin()->first, 1);


    QCOMPARE(emptyMap.mbegin(), emptyMap.mend());
    QCOMPARE(constEmptyMap.mbegin(), constEmptyMap.mend());

    auto mit = pseudoEmptyMap.mbegin();
    QCOMPARE(mit->first, 2);
    ++mit;
    QCOMPARE(mit, pseudoEmptyMap.mend());
    auto cmit = constPseudoEmptyMap.mbegin();
    QCOMPARE(cmit->first, 2);
    ++cmit;
    QCOMPARE(cmit, constPseudoEmptyMap.mend());

    QCOMPARE(map.mbegin()->first, 1);
    QCOMPARE(constMap.mbegin()->first, 1);
}

void ComposedMapTest::mendTest()
{
    auto pvit = pseudoEmptyVect.mend();
    --pvit;
    QCOMPARE(pvit->first, 1);
    auto cpvit = constPseudoEmptyVect.mend();
    --cpvit;
    QCOMPARE(cpvit->first, 1);

    auto vit = vect.mend();
    --vit;
    QCOMPARE(vit->first, 3);
    auto cvit = constVect.mend();
    --cvit;
    QCOMPARE(cvit->first, 3);


    auto pmit = pseudoEmptyMap.mend();
    --pmit;
    QCOMPARE(pmit->first, 2);
    auto cpmit = constPseudoEmptyMap.mend();
    --cpmit;
    QCOMPARE(cpmit->first, 2);

    auto mit = map.mend();
    --mit;
    QCOMPARE(mit->first, 3);
    auto cmit = constMap.mend();
    --cmit;
    QCOMPARE(cmit->first, 3);
}

void ComposedMapTest::emptyTest()
{
    QCOMPARE(emptyVect.empty(), true);
    QCOMPARE(emptyVect.empty(1), true);

    QCOMPARE(pseudoEmptyVect.empty(), true);
    QCOMPARE(pseudoEmptyVect.empty(1), true);
    QCOMPARE(pseudoEmptyVect[1].empty(), true);

    QCOMPARE(vect.empty(), false);
    QCOMPARE(vect.empty(1), false);
    QCOMPARE(vect[1].empty(), false);


    QCOMPARE(emptyMap.empty(), true);
    QCOMPARE(emptyMap.empty(2), true);

    QCOMPARE(pseudoEmptyMap.empty(), true);
    QCOMPARE(pseudoEmptyMap.empty(2), true);
    QCOMPARE(pseudoEmptyMap[2].empty(), true);

    QCOMPARE(map.empty(), false);
    QCOMPARE(map.empty(2), false);
    QCOMPARE(map[2].empty(), false);
}

void ComposedMapTest::elementsCountTest()
{
    QCOMPARE(emptyVect.elementsCount(), 0u);
    QCOMPARE(pseudoEmptyVect.elementsCount(), 0u);
    QCOMPARE(vect.elementsCount(), 6u);

    QCOMPARE(emptyMap.elementsCount(), 0u);
    QCOMPARE(pseudoEmptyMap.elementsCount(), 0u);
    QCOMPARE(map.elementsCount(), 6u);
}

void ComposedMapTest::clearTest()
{
    ComposedMap<int, std::vector<std::string>> vect = createVectComposedMap();
    ComposedMap<int, std::map<char, std::string>> map = createMapComposedMap();

    QCOMPARE(vect.empty(3), false);
    vect.clear(3);
    QCOMPARE(vect.empty(3), true);

    QCOMPARE(vect.empty(), false);
    vect.clear();
    QCOMPARE(vect.empty(), true);


    QCOMPARE(map.empty(1), false);
    map.clear(1);
    QCOMPARE(map.empty(1), true);

    QCOMPARE(map.empty(), false);
    map.clear();
    QCOMPARE(map.empty(), true);
}

void ComposedMapTest::eraseTest()
{
    ComposedMap<int, std::vector<std::string>> vect = createVectComposedMap();
    ComposedMap<int, std::map<char, std::string>> map = createMapComposedMap();


    /** erase(iterator position); **/

    QCOMPARE(emptyVect.erase(emptyVect.cbegin()), emptyVect.end());
    QCOMPARE(emptyVect.erase(emptyVect.begin()), emptyVect.end());
    QCOMPARE(pseudoEmptyVect.erase(pseudoEmptyVect.cbegin()), pseudoEmptyVect.end());
    QCOMPARE(pseudoEmptyVect.erase(pseudoEmptyVect.begin()), pseudoEmptyVect.end());
    QCOMPARE(pseudoEmptyVect.size(), 1ul);

    QCOMPARE(vect.elementsCount(), 6u);
    auto vnext = vect.erase(vect.cbegin());
    QCOMPARE(vect.elementsCount(), 5u);
    QCOMPARE(vnext, vect.begin());
    QCOMPARE(*vnext, std::string("2"));
    QCOMPARE(vect[1].at(0), std::string("2"));
    QCOMPARE(vect[1].at(1), std::string("3"));

    ++vnext;

    auto vnext2 = vect.erase(vnext);
    QCOMPARE(vect.elementsCount(), 4u);
    QCOMPARE(*vnext2, std::string("4"));

    ++vnext2;
    ++vnext2;

    auto vnext3 = vect.erase(vnext2);
    QCOMPARE(vect.elementsCount(), 3u);
    QCOMPARE(vnext3, vect.end());

    auto vnext4 = vect.erase(vnext3);
    QCOMPARE(vect.elementsCount(), 3u);
    QCOMPARE(vnext4, vect.end());



    QCOMPARE(emptyMap.erase(emptyMap.cbegin()), emptyMap.end());
    QCOMPARE(emptyMap.erase(emptyMap.begin()), emptyMap.end());
    QCOMPARE(pseudoEmptyMap.erase(pseudoEmptyMap.cbegin()), pseudoEmptyMap.end());
    QCOMPARE(pseudoEmptyMap.erase(pseudoEmptyMap.begin()), pseudoEmptyMap.end());
    QCOMPARE(pseudoEmptyMap.size(), 1ul);

    QCOMPARE(map.elementsCount(), 6u);
    auto mnext = map.erase(map.cbegin());
    QCOMPARE(map.elementsCount(), 5u);
    QCOMPARE(mnext, map.begin());
    QCOMPARE(*mnext, std::string("2"));
    QCOMPARE(map[1].at('b'), std::string("2"));
    QCOMPARE(map[1].at('c'), std::string("3"));

    ++mnext;

    auto mnext2 = map.erase(mnext);
    QCOMPARE(map.elementsCount(), 4u);
    QCOMPARE(*mnext2, std::string("4"));

    ++mnext2;
    ++mnext2;

    auto mnext3 = map.erase(mnext2);
    QCOMPARE(map.elementsCount(), 3u);
    QCOMPARE(mnext3, map.end());

    auto mnext4 = map.erase(mnext3);
    QCOMPARE(map.elementsCount(), 3u);
    QCOMPARE(mnext4, map.end());


    /** erase(const Key& k) **/

    QCOMPARE(emptyVect.erase(1), 0ul);
    QCOMPARE(pseudoEmptyVect.erase(1), 1ul);

    QCOMPARE(vect.count(1), 1ul);
    QCOMPARE(vect.erase(1), 1ul);
    QCOMPARE(vect.count(1), 0ul);
    QCOMPARE(vect.elementsCount(), 2u);


    QCOMPARE(emptyMap.erase(1), 0ul);
    QCOMPARE(pseudoEmptyMap.erase(2), 1ul);

    QCOMPARE(map.count(1), 1ul);
    QCOMPARE(map.erase(1), 1ul);
    QCOMPARE(map.count(1), 0ul);
    QCOMPARE(map.elementsCount(), 2u);


    /** erase(iterator first, iterator last); **/

    ComposedMap<int, std::vector<std::string>> otherVect = createVectComposedMap();
    ComposedMap<int, std::map<char, std::string>> otherMap = createMapComposedMap();


    QCOMPARE(otherVect.erase(otherVect.end(), otherVect.end()), otherVect.end());
    QCOMPARE(otherVect.elementsCount(), 6u);

    auto vfirst = otherVect.begin();
    ++vfirst;
    auto vlast = vfirst;
    ++vlast;
    ++vlast;
    ++vlast;
    ++vlast;
    auto otherVnext = otherVect.erase(vfirst, vlast);

    QCOMPARE(otherVect.elementsCount(), 2u);
    QCOMPARE(*otherVnext, std::string("6"));

    auto otherVnext2 = otherVect.erase(otherVnext, otherVect.end());
    QCOMPARE(otherVect.elementsCount(), 1u);
    QCOMPARE(otherVnext2, otherVect.end());


    QCOMPARE(otherMap.erase(otherMap.end(), otherMap.end()), otherMap.end());
    QCOMPARE(otherMap.elementsCount(), 6u);

    auto mfirst = otherMap.begin();
    ++mfirst;
    auto mlast = mfirst;
    ++mlast;
    ++mlast;
    ++mlast;
    ++mlast;
    auto otherMnext = otherMap.erase(mfirst, mlast);

    QCOMPARE(otherMap.elementsCount(), 2u);
    QCOMPARE(*otherMnext, std::string("6"));

    auto otherMnext2 = otherMap.erase(otherMnext, otherMap.end());
    QCOMPARE(otherMap.elementsCount(), 1u);
    QCOMPARE(otherMnext2, otherMap.end());
}

QTEST_APPLESS_MAIN(ComposedMapTest)

#include "tst_ComposedMapTest.moc"
