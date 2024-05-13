//
// Created by zsotroav on 2024-05-11.
//

#include "test.h"
#include "gtest_lite.h"
#include <string>

#include "action.h"
#include "brand.h"
#include "common.h"
#include "overlord.h"
#include "player.h"
#include "server.h"

#include "memtrace.h"

using namespace plushies;

void dotest() {
    /// action.h

    Action testAction1 = NullAction;
    Action testAction2 = NullAction;

    TEST(Action ctor, Test thow/no throw) {

        EXPECT_NO_THROW( testAction1 = Action("Test Action", 100, 100, 5, 2, NORMAL, Physical) );
        EXPECT_THROW(testAction2 = Action("Throw", 10, 200, 5, 2, NORMAL, Physical), std::invalid_argument );

    } ENDM


    TEST(Action ctor, Test Action ctor) {
        // Test is ctor initialized everything properly
        EXPECT_TRUE(std::string("Test Action") == testAction1.getName());
        EXPECT_EQ( 100, testAction1.getDamage() );
        EXPECT_EQ( 100, testAction1.getAccuracy() );
        EXPECT_EQ( 5, testAction1.getMaxEnergy() );
        EXPECT_DOUBLE_EQ( 2, testAction1.getPriority() );
        EXPECT_EQ( Type::NORMAL, testAction1.getType() );
        EXPECT_EQ( ActionCategory::Physical, testAction1.getCategory() );
    } ENDM

    TEST(Action Energy, DecEnergy) {
        EXPECT_EQ( 5, testAction1.getMaxEnergy() );  // Max Energy is 5
        testAction1.decEnergy();                     // Decrement (use) energy
        EXPECT_EQ( 4, testAction1.getEnergy() );     // Available en. is 4
        EXPECT_EQ( 5, testAction1.getMaxEnergy() );  // Max should still be 5
    } ENDM

    /// brand.h


    /// common.h

    // Type relation

    TEST(Type relation 1, GRASS > WATER) {
        EXPECT_DOUBLE_EQ( 2, Type::GRASS >> Type::WATER );
    } ENDM

    TEST(Type relation 2, WATER > GRASS) {
        EXPECT_DOUBLE_EQ( 0.5, Type::WATER >> Type::GRASS );
    } ENDM

    TEST(Type relation 3, NORMAL > GHOST) {
        EXPECT_DOUBLE_EQ( 0, Type::NORMAL >> Type::GHOST );
    } ENDM

    ///
}