#include "model.hxx"
#include <catch.hxx>


TEST_CASE("Default parameters are properly assigned")
{
    Model m = Model();

    CHECK(m.main.HP() == 100);
    CHECK(m.frozen == false);
    CHECK(m.win == false);
    CHECK(m.over == false);
    CHECK(m.over == false);
    CHECK(m.a_key == false);
    CHECK(m.d_key == false);
}

TEST_CASE("All timers work correctly")
{
    // Timers include frozen state of screen, invincibility of character and enemies, sword counter
    Model m = Model();

    m.swing_retract_sword(true);
    m.frozen = true;
    m.do_damage_main(1);


    // Increment by a little over half a second
    // Must do loop as counter increments every time on_frame is called
    for (size_t i = 0; i < 31; i++) {
        m.on_frame(i);
    }
    CHECK(m.main.hitbox_active() == false);

    // increment the tie by a little over 1.5 more seconds
    for (size_t i = 0; i < 91; i++) {
        m.on_frame(i);
    }
    CHECK(m.main.invincibility() == false);

    // Increment by a little over 5 more seconds
    for (size_t i = 0; i < 300; i++) {
        m.on_frame(i);
    }
    CHECK(m.frozen == false);
}


TEST_CASE("Game Progression"){

    // All enemies spawn in correctly
    Model m = Model();

    // Give the player so much HP to the point where they should not die i
    m.do_damage_main(-100000);
    m.change_y_velocity(10000); // Should keep the player up top and unavailable

    // Check enemy spawns in intervals
    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 2);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 3);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 4);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 5);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 6);

    // Check first enemy spawned
    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 7);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 9);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 10);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 12);

    for (size_t i = 0; i < 301; i++) {
        m.on_frame(i);
    }
    CHECK(m.enemy_counter == 13);

    // // Kill All Enemies and check that game was over and won
    // for (Enemy& enemy_: m.enemies) {
    //     enemy_ = m.do_damage_en(enemy_, 40);
    // }
    m.enemies[0] = m.do_damage_en(m.enemies[0], 40);
    m.enemies[1] = m.do_damage_en(m.enemies[1], 40);
    m.enemies[2] = m.do_damage_en(m.enemies[2], 40);
    m.enemies[3] = m.do_damage_en(m.enemies[3], 40);
    m.enemies[4] = m.do_damage_en(m.enemies[4], 40);
    m.enemies[5] = m.do_damage_en(m.enemies[5], 40);
    m.enemies[6] = m.do_damage_en(m.enemies[6], 40);
    m.enemies[7] = m.do_damage_en(m.enemies[7], 40);
    m.enemies[8] = m.do_damage_en(m.enemies[8], 40);
    m.enemies[9] = m.do_damage_en(m.enemies[9], 40);
    m.enemies[10] = m.do_damage_en(m.enemies[10], 40);
    m.enemies[11] = m.do_damage_en(m.enemies[11], 40);
    m.enemies[12] = m.do_damage_en(m.enemies[12], 40);

    m.on_frame(1);
    CHECK(m.all_dead(m.enemies) == true);
    CHECK(m.over == true);
    CHECK(m.win == true);


    // Kill the player this time
    Model d = Model();

    // Kill the player
    d.do_damage_main(100);
    d.on_frame(1);
    CHECK(d.main.HP() == 0);
    CHECK(d.over == true);
    CHECK(d.win == false);
}

TEST_CASE("Items Work Correctly"){

    // All enemies spawn in correctly
    Model m = Model();

    // Set the heart to the player's position
    m.heart = Heart({400, 500, 10, 10});

    // Player shouldn't have taken any damage yet so heart should still be
    // there after time
    m.on_frame(2);
    CHECK(m.heart.detection_box().x == 400);
    CHECK(m.main.HP() == 100);

    // Now that main in damaged, they should take heart
    m.do_damage_main(10);
    CHECK(m.main.HP() == 90);
    m.on_frame(2);
    CHECK(m.main.HP() == 100);
    CHECK(m.heart.detection_box().x != 400);


    // Spawn freeze at main player position
    m.freeze = Freeze({400,500,10,10});
    m.enemies.push_back(Enemy(ge211::geometry::Posn<float>(700,500),
            {0, 0},30, true, false, 0));
    for (size_t i = 2; i < 130; i++) {
        m.on_frame(i);
    }
    auto x = m.enemies[0].position().x;

    for (size_t i = 131; i < 150; i++) {
        m.on_frame(i);
    }

    CHECK(x == m.enemies[0].position().x);
}

TEST_CASE("Damage Correctly") {
    // Damage increments correctly for main and enemies, and activates invinc.
    Model m = Model();

    m.do_damage_main(5);
    CHECK(m.main.invincibility() == true);
    CHECK(m.main.HP() == 95);

    m.enemies.push_back(Enemy(ge211::geometry::Posn<float>(700,500),
            {0, 0},30, true, false, 0));

    m.enemies[0] = m.do_damage_en(m.enemies[0], 10);
    CHECK(m.enemies[0].HP() == 20);
    CHECK(m.enemies[0].invincibility() == true);

    // Damage increments correctly for main and enemies, and activates invinc.
    Model d = Model();

    // Spawn enemy in same position as player and ensure they took 10 damage
    d.enemies.push_back(Enemy(ge211::geometry::Posn<float>(410,500),
                              {0, 0},30, false, false, 0));
    d.on_frame(1);
    CHECK(d.main.HP() == 90);

    // Swing the sword and check it made damage on the enemy
    d.swing_retract_sword(true);
    d.on_frame(1);
    CHECK(d.enemies[0].HP() == 20);
}

TEST_CASE("Movement Works Correctly"){
    Model m = Model();
    m.enemies.push_back(Enemy(ge211::geometry::Posn<float>(10,500),
                              {0, 0},30, false, false, 0));

    m.do_damage_main(-100000000);

    CHECK(m.main.position().x == 400);
    m.a_key = true;
    m.on_frame(1);
    CHECK(m.main.position().x == 200);

    // Make sure they don't move past the edge
    m.on_frame(1000);
    CHECK(m.main.position().x > 0);

}