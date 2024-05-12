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
    Action testAction = {"Test Action", 100, 100, 5, 2, NORMAL, Physical};

    TEST(Action ctor, Test Action ctor) {
        // Test is ctor initialized everything properly
        EXPECT_TRUE(std::string("Test Action") == testAction.getName());
        EXPECT_EQ( 100, testAction.getDamage() );
        EXPECT_EQ( 100, testAction.getAccuracy() );
        EXPECT_EQ( 5, testAction.getMaxEnergy() );
        EXPECT_DOUBLE_EQ( 2, testAction.getPriority() );
        EXPECT_EQ( Type::NORMAL, testAction.getType() );
        EXPECT_EQ( ActionCategory::Physical, testAction.getCategory() );
    } ENDM

    TEST(Action Energy, DecEnergy) {
        EXPECT_EQ( 5, testAction.getMaxEnergy() );  // Max Energy is 5
        testAction.decEnergy();                     // Decrement (use) energy
        EXPECT_EQ( 4, testAction.getEnergy() );     // Available en. is 4
        EXPECT_EQ( 5, testAction.getMaxEnergy() );  // Max should still be 5
    } ENDM

    /// brand.h


    /// common.h

    /// Type relation

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