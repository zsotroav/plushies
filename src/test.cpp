#include "test.h"
#include "gtest_lite.h"
#include <string>

#include "action.h"
#include "brand.h"
#include "common.h"
#include "player.h"
#include "plush.h"
#include "server.h"
#include "overlord.h"

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

    TEST(Action, failexcep) {
        auto e = FailedAction();
        EXPECT_TRUE(std::string("Action failed!") == std::string(e.what()));
    } END

    /// brand.h

    int st[] = {100, 90, 45, 45, 80, 60 };
    Brand testBrand  = { "Test brand", NORMAL, NONE, st};
    Brand testBrand2 = { "Test brand 2", FIRE, WATER, st};

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
        const std::string   base =  "asdfghjkléáőúűöüóí";
        const std::wstring wbase = L"asdfghjkléáőúűöüóí";

        EXPECT_TRUE(wbase == convertUFT8(base));
        EXPECT_TRUE(base == convertFromUFT8(wbase));

        std::wstringstream ss;
        ss << base;
        EXPECT_TRUE(ss.str() == wbase);
    } ENDM

    // wostream operators
    TEST(common, wostream.type) {
        std::wstringstream ss;
        ss << FLYING << ELECTRIC;
        EXPECT_TRUE(ss.str() == std::wstring(L"FLYING  ELECTRIC"));
    } END

    TEST(common, wostream.gm) {
        std::wstringstream ss;
        ss << RANDOM << " " << CUSTOM;
        EXPECT_TRUE(ss.str() == std::wstring(L"Random Custom"));
    } END

    TEST(common, wostream.ac) {
        std::wstringstream ss;
        ss << Physical << " " << Special;
        EXPECT_TRUE(ss.str() == std::wstring(L"PHYSICAL SPECIAL "));
    } END

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


    TEST(common, split semicolon) {
        const std::vector<string> v = { "a", "b", "c", "d"};

        const auto test = split("a;b;c;d", ';');

        EXPECT_EQ(v.size(), test.size());

        for (size_t i = 0; i < v.size(); ++i) {
            if (v[i] == test[i]) continue;
            FAIL() << "Items do not match: " << v[i] << " - " << test[i];
        }

    } ENDM

    TEST(common.lan, encode) {
        EXPECT_TRUE("ADEF"    == encodeChoice(0));
        EXPECT_TRUE("ASWP 1"  == encodeChoice(-1));
        EXPECT_TRUE("AATK 1"  == encodeChoice(1));
        EXPECT_TRUE("AATK 11" == encodeChoice(11));
    } ENDM

    TEST(common.lan, decode) {
        EXPECT_TRUE(0  == decodeChoice("ADEF"));
        EXPECT_TRUE(-1 == decodeChoice("ASWP 1"));
        EXPECT_TRUE(1  == decodeChoice("AATK 1"));
        EXPECT_TRUE(11 == decodeChoice("AATK 11"));
    } ENDM

    /// Plush

    const int UVOK[] = { 10, 10, 10, 10, 10, 10 };
    const int UVHI[] = { 65, 10, 10, 10, 10, 10 };
    const int UVLO[] = { -1, 10, 10, 10, 10, 10 };

    Action ac = { "Test Action", 100, 100, 1, 2, NORMAL, Physical };

    Action Actions[] = { ac, ac, ac, ac };
    Action NullAcs[] = { NullAction, NullAction, NullAction, NullAction };

    TEST(plush, ctor) {
        EXPECT_NO_THROW(Plush(testBrand, UVOK, Actions));
        EXPECT_NO_THROW(Plush(testBrand, UVOK, NullAcs));
        EXPECT_THROW(Plush(testBrand, UVHI, Actions), std::invalid_argument const&);
        EXPECT_THROW(Plush(testBrand, UVLO, Actions), std::invalid_argument const&);
    } ENDM

    Plush p1 = {testBrand,  UVOK, Actions};
    Plush p2 = {testBrand2, UVOK, NullAcs};

    TEST(plush, ctor.valid) {
        EXPECT_EQ(testBrand.getName(), p1.getName());
        for (int i = 0; i < 6; ++i)
            if (p1.getUV(static_cast<StatOrder>(i)) != 10) FAIL() << "UV";
        for (int i = 0; i < 4; ++i) if (!(p1.Actions[i] == ac)) FAIL() << "AC";
    } END

    TEST(plush, HP) {
        int hp = p1.getHP();
        EXPECT_EQ(p1.getHP(), p1.getMaxHP());
        p1 << 1;
        EXPECT_EQ(hp-1, p1.getHP());
        EXPECT_EQ(hp, p1.getMaxHP());
    } END

    TEST(plush, AC) {
        EXPECT_NO_THROW(p1.getSafeAC(1));
        EXPECT_THROW(p2.getSafeAC(1), std::invalid_argument const&);
        EXPECT_NO_THROW(p1.operator>>(1));
        EXPECT_THROW(p1.operator>>(1), FailedAction const&); // Out of energy
    } END

    TEST(plush, damage) {
        auto pcpy = p1; // Copy to not mess with other tests
        const int hp = pcpy.getHP();
        EXPECT_NO_THROW(pcpy << (pcpy >> 0));
        EXPECT_NE(hp, pcpy.getHP());
    } END

    TEST(plush, damage) {
        auto pcpy = p1; // Copy to not mess with other tests
        const int hp = pcpy.getHP();
        EXPECT_NO_THROW(pcpy << (pcpy.getAC(0)));
        EXPECT_NE(hp, pcpy.getHP());
    } END

    TEST(plush, validMoves) {
        EXPECT_EQ(4, p1.validMoves());
        EXPECT_EQ(0, p2.validMoves());
    } END

    TEST(plush, validateAC) {
        EXPECT_TRUE(p1.validateAC(0));
        EXPECT_TRUE(p1.validateAC(p1.Actions[0]));
        EXPECT_FALSE(p2.validateAC(0));
        EXPECT_FALSE(p2.validateAC(p2.Actions[0]));
    } END

    TEST(plush, calcSpeed.Throw) {
        EXPECT_NO_THROW(p1.calcDamage(0));
        EXPECT_NO_THROW(p1.calcSpeed(0));

        EXPECT_ANY_THROW(p1.calcDamage(4));
    } END

    /// Player

    Player pl;

    TEST(player, addplush) {
        pl.addPlush(p1);
        pl.addPlush(p2);

        auto act = pl.getActivePlush();

        EXPECT_EQ(2, pl.numPlushes());
        EXPECT_EQ(2, pl.numPlushes(true));
        EXPECT_EQ(2, pl.getPlushes().size());
        EXPECT_EQ(p1.getName(), act.getName());
        EXPECT_TRUE(p1.getBrand() == act.getBrand());
        EXPECT_TRUE(p1.Actions[0] == act.Actions[0]);
        EXPECT_TRUE(ac == pl.activeAction(0));
    } END

    TEST(player, setActive ) {
        EXPECT_THROW(pl.setActive(2), std::invalid_argument const&); // Inv
        EXPECT_THROW(pl.setActive(0), std::invalid_argument const&); // Curr
        EXPECT_NO_THROW(pl.setActive(1));
    } END

    TEST(player, numPlushes) {
        pl.active() << pl.active().getMaxHP() + 10; // For sure dead
        EXPECT_EQ(1, pl.numPlushes(true));  // One dead
        EXPECT_EQ(2, pl.numPlushes(false)); // We still have two in total
    } END

    TEST(player, nextAlive) {
        auto act = pl.getActivePlush();
        EXPECT_EQ(p2.getName(), act.getName());
        EXPECT_TRUE(p2.getBrand() == act.getBrand());
        EXPECT_TRUE(p2.Actions[0] == act.Actions[0]);
        pl.nextAlive();
        auto nex = pl.getActivePlush();
        EXPECT_EQ(p1.getName(), nex.getName());
        EXPECT_TRUE(p1.getBrand() == nex.getBrand());
        EXPECT_TRUE(p1.Actions[0] == nex.Actions[0]);
    } END

    TEST(player, setActive.dead ) {
        EXPECT_THROW(pl.setActive(0), std::invalid_argument const&); // Curr
        EXPECT_THROW(pl.setActive(1), std::invalid_argument const&); // dead
    } END

    /// server.h

    TEST(server, readCSV) {
        std::istringstream ifs("asd;fgh;jkl;éáű");
        auto vec = readCSV(ifs);
        EXPECT_EQ(4, vec.size());
        EXPECT_EQ(std::string("asd"), vec[0]);
        EXPECT_EQ(std::string("fgh"), vec[1]);
        EXPECT_EQ(std::string("jkl"), vec[2]);
        EXPECT_EQ(std::string("éáű"), vec[3]);
    } ENDM

    TEST(server, init) {
        try {
            Server s = Server(OVERLORD_CLYDE, RANDOM, 1);

            auto n = overlord::Ninty(s, 1);
            int re_den = n.ready(n.active());
            EXPECT_TRUE(re_den >= 0 && re_den <= 4);

            s.RegisterPlayer(new Player(pl), 1);
            EXPECT_EQ(RANDOM, s.getGameMode());
            EXPECT_EQ(OVERLORD_CLYDE, s.getLanMode());
            EXPECT_EQ(false, s.againstLAN());

            if (s.actions.size() == 0) FAIL() << "No actions";
            if (s.brands.size() == 0 ) FAIL() << "No brands";

            EXPECT_EQ(1, s.getPlayer(0)->numPlushes());

        } catch (...) {
            FAIL() << "Something threw an error";
        }
    } END

    delete ac1;
    delete ac2;
}