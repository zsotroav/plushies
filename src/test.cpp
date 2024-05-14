#include "test.h"
#include "gtest_lite.h"
#include <string>

#include "action.h"
#include "brand.h"
#include "common.h"
#include "overlord.h"
#include "player.h"
#include "plush.h"
#include "server.h"

#include "memtrace.h"

using namespace plushies;

void dotest() {
    /// action.h

    Action testAction1 = NullAction;
    Action testAction2 = NullAction;

    TEST(Action ctor, Test thow/no throw) {

        EXPECT_NO_THROW( testAction1 = Action("Test Action", 100, 100, 5, 2, NORMAL, Physical) );

        try {
            testAction2 = Action("Throw", 10, 200, 5, 2, NORMAL, Physical);
            FAIL() << "Expected std::invalid_argument";
        } catch (std::invalid_argument const & e) {
            EXPECT_STREQ(e.what(), "Invalid accuracy");
        } catch (...) {
            FAIL() << "Expected std::invalid_argument";
        }

    } END


    TEST(Action ctor, Test Action ctor) {
        // Test is ctor initialized everything properly
        EXPECT_TRUE(std::string("Test Action") == testAction1.getName());
        EXPECT_EQ( 100, testAction1.getDamage() );
        EXPECT_EQ( 100, testAction1.getAccuracy() );
        EXPECT_EQ( 5, testAction1.getMaxEnergy() );
        EXPECT_DOUBLE_EQ( 2, testAction1.getPriority() );
        EXPECT_EQ( Type::NORMAL, testAction1.getType() );
        EXPECT_EQ( ActionCategory::Physical, testAction1.getCategory() );
    } END

    TEST(Action Energy, DecEnergy) {
        EXPECT_EQ( 5, testAction1.getMaxEnergy() );  // Max Energy is 5
        testAction1.decEnergy();                     // Decrement (use) energy
        EXPECT_EQ( 4, testAction1.getEnergy() );     // Available en. is 4
        EXPECT_EQ( 5, testAction1.getMaxEnergy() );  // Max should still be 5
    } END

    /// brand.h

    int st[] = {100, 90, 45, 45, 80, 60 };
    Brand testBrand = { "Test brand", Type::NORMAL, Type::NONE, st};

    TEST(Brand ctor, ctor/getter validate) {
        EXPECT_TRUE(std::string("Test brand") == testBrand.getName());
        EXPECT_EQ(NORMAL, testBrand.getBaseType());
        EXPECT_EQ(NONE, testBrand.getSecondaryType());
        EXPECT_EQ(420, testBrand.baseStatTotal());

        EXPECT_EQ(100, testBrand.getBaseStat(StatOrder::HP));
        EXPECT_EQ( 90, testBrand.getBaseStat(StatOrder::Atk));
        EXPECT_EQ( 45, testBrand.getBaseStat(StatOrder::Def));
        EXPECT_EQ( 45, testBrand.getBaseStat(StatOrder::Spe));
        EXPECT_EQ( 80, testBrand.getBaseStat(StatOrder::SpD));
        EXPECT_EQ( 60, testBrand.getBaseStat(StatOrder::SpA));
    } END

    TEST(Brand ctor, Action list empty) {
        EXPECT_EQ(0, testBrand.getLearnableActions().size());
    } END

    const auto ac1 = new Action(testAction1); // Should be a valid action
    const auto ac2 = new Action(NullAction);  // Is known to be invalid

    TEST(Brand learnable actions, Add actions) {
        EXPECT_NO_THROW(testBrand.addLearnableAction(ac1));

        try {
            testBrand.addLearnableAction(ac2);
            FAIL() << "Expected std::invalid_argument";
        } catch (std::invalid_argument const & e) {
            EXPECT_STREQ(e.what(), "Invalid action");
        } catch (...) { FAIL() << "Expected std::invalid_argument"; }

        EXPECT_EQ(1, testBrand.getLearnableActions().size());

    } END

    /// common.h

    // Can not test random

    // Type relations
    TEST(common.type, GRASS > WATER) {
        EXPECT_DOUBLE_EQ( 2, Type::GRASS >> Type::WATER );
    } END

    TEST(common.type, WATER > GRASS) {
        EXPECT_DOUBLE_EQ( 0.5, Type::WATER >> Type::GRASS );
    } END

    TEST(common.type, NORMAL > GHOST) {
        EXPECT_DOUBLE_EQ( 0, Type::NORMAL >> Type::GHOST );
    } END

    // convertUTF8
    TEST(common, convert UTF8) {
        const string base = "asdfghjkléáőúűöüóí";
        const wstring wbase = L"asdfghjkléáőúűöüóí";

        EXPECT_TRUE(wbase == convertUFT8(base));
        EXPECT_TRUE(base == convertFromUFT8(wbase));

    } ENDM

    // wostream operators meh

    // split
    TEST(common, split space) {
        const std::vector<string> v = { "a", "b", "c", "d"};

        const auto test = split("a b c d", ' ');

        EXPECT_EQ(v.size(), test.size());

        for (size_t i = 0; i < v.size(); ++i) {
            if (v[i] == test[i]) continue;
            FAIL() << "Items do not match: " << v[i] << " - " << test[i];
        }

    } ENDM


    TEST(common, split semicolumn) {
        const std::vector<string> v = { "a", "b", "c", "d"};

        const auto test = split("a;b;c;d", ';');

        EXPECT_EQ(v.size(), test.size());

        for (size_t i = 0; i < v.size(); ++i) {
            if (v[i] == test[i]) continue;
            FAIL() << "Items do not match: " << v[i] << " - " << test[i];
        }

    } ENDM

    ///

    delete ac1;
    delete ac2;
}