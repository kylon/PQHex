/*
 * This file is part of PQHex.
 * Copyright (C) 2025 kylon
 *
 * PQHex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PQHex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>

#include "../../../../../include/quest/SaveCharacterPoteintialData.h"

namespace PQH::UI {
    class PotentialSkillDataEditor final: public QWidget {
        Q_OBJECT

    private:
        struct Move_t {
            std::string_view name;
            short id;
            short damage;
            short wait;
            std::string_view icon;
        };

        struct MoveSet_t {
            int setLimit;
            int setIdx;
        };

        enum class PMove {
            Explosion = 0,
            GigaImpact,
            HyperBeam,
            Splash,
            BellyDrum,
            Transform,
            Scratch,
            Roar,
            Whirlwind,
            Stomp,
            Flash,
            WorkUp,
            SelfDestruct,
            Flail,
            Harden,
            FocusEnergy,
            FollowMe,
            MegaPunch,
            FurySwipes,
            Substitute,
            Growl,
            Rest,
            Leer,
            CometPunch,
            ExtremeSpeed,
            Tackle,
            EggBomb,
            SoftBoiled,
            Slam,
            TriAttack,
            TakeDown,
            SwordsDance,
            Supersonic,
            Sing,
            Recover,
            PetalDance,
            RazorLeaf,
            Spore,
            Synthesis,
            MegaDrain,
            StunSpore,
            SolarBeam,
            BulletSeed,
            VineWhip,
            LeechSeed,
            FireBlast,
            Ember,
            FirePunch,
            FireSpin,
            LavaPlume,
            FlareBlitz,
            FlameWheel,
            Flamethrower,
            HeatWave,
            FlameCharge,
            WillOWisp,
            RockTomb,
            RockThrow,
            Rollout,
            RockBlast,
            RockPolish,
            Sandstorm,
            StealthRock,
            SilverWind,
            RagePowder,
            StringShot,
            LeechLife,
            Megahorn,
            PinMissile,
            Lunge,
            UTurn,
            VoltTackle,
            ThunderShock,
            ElectricTerrain,
            Electroweb,
            Thunder,
            ThunderPunch,
            Spark,
            Charge,
            Thunderbolt,
            Barrier,
            Amnesia,
            LightScreen,
            Agility,
            Psybeam,
            Psystrike,
            PsychoCut,
            Psychic,
            Hypnosis,
            ZenHeadbutt,
            Teleport,
            Meditate,
            AquaRing,
            AquaJet,
            Bubble,
            HydroPump,
            Withdraw,
            Surf,
            Waterfall,
            Whirlpool,
            DynamicPunch,
            BulkUp,
            DrainPunch,
            PowerUpPunch,
            CloseCombat,
            RockSmash,
            CrossChop,
            RollingKick,
            HighJumpKick,
            Submission,
            Dig,
            MudBomb,
            MudSlap,
            Bonemerang,
            Earthquake,
            Spikes,
            ShoreUp,
            VenomDrench,
            PoisonSting,
            Toxic,
            PoisonPowder,
            SludgeBomb,
            Smog,
            AcidArmor,
            Hurricane,
            DrillPeck,
            SkyAttack,
            Roost,
            Gust,
            Tailwind,
            Fly,
            Bounce,
            AerialAce,
            IronTail,
            SteelWing,
            MetalSound,
            MetalClaw,
            FlashCannon,
            IronDefense,
            Blizzard,
            IcyWind,
            AuroraVeil,
            IceBeam,
            IcePunch,
            IcicleCrash,
            SuckerPunch,
            Crunch,
            Flatter,
            NightSlash,
            Taunt,
            NastyPlot,
            ConfuseRay,
            Astonish,
            Lick,
            ShadowBall,
            Charm,
            DrainingKiss,
            DazzlingGleam,
            SweetKiss,
            PlayRough,
            DragonRush,
            DragonClaw,
            Outrage,
            DragonPulse,
            DragonDance,
            DracoMeteor,
            Twister,
            BaseMeleeBug,
            BaseRangedBug,
            BaseMeleeDark,
            BaseRangedDark,
            BaseMeleeDragon,
            BaseRangedDragon,
            BaseMeleeElectric,
            BaseRangedElectric,
            BaseMeleeFairy,
            BaseRangedFairy,
            BaseMeleeFighting,
            BaseRangedFighting,
            BaseMeleeFire,
            BaseRangedFire,
            BaseMeleeFlying,
            BaseRangedFlying,
            BaseMeleeGhost,
            BaseRangedGhost,
            BaseMeleeGrass,
            BaseRangedGrass,
            BaseMeleeGround,
            BaseRangedGround,
            BaseMeleeIce,
            BaseRangedIce,
            BaseMeleeNormal,
            BaseRangedNormal,
            BaseMeleePoison,
            BaseRangedPoison,
            BaseMeleePsychic,
            BaseRangedPsychic,
            BaseMeleeRock,
            BaseRangedRock,
            BaseMeleeSteel,
            BaseRangedSteel,
            BaseMeleeWater,
            BaseRangedWater
        };

        static constexpr std::array<Move_t, 203> MovesData = {{
            {"Explosion", 181, 683, 5, "explosion"},
            {"Giga Impact", 238, 176, 5, "gigaimpact"},
            {"Hyper Beam", 40, 300, 10, "hyperbeam"},
            {"Splash", 165, 56, 3, "splash"},
            {"Belly Drum", 195, 0, 5, "bellydrum"},
            {"Transform", 242, 0, 0, "transform"},
            {"Scratch", 161, 231, 5, "scratch"},
            {"Roar", 197, 0, 2, "roar"},
            {"Whirlwind", 183, 0, 2, "whirlwind"},
            {"Stomp", 174, 180, 5, "stomp"},
            {"Flash", 186, 0, 2, "flash"},
            {"Work Up", 235, 0, 8, "workup"},
            {"Self-Destruct", 236, 494, 5, "self-destruct"},
            {"Flail", 221, 130, 5, "flail"},
            {"Harden", 173, 0, 5, "harden"},
            {"Focus Energy", 172, 0, 5, "focusenergy"},
            {"Follow Me", 170, 0, 2, "followme"},
            {"Mega Punch", 168, 561, 5, "megapunch"},
            {"Fury Swipes", 187, 146, 5, "furyswipes"},
            {"Substitute", 182, 0, 5, "substitute"},
            {"Growl", 176, 0, 4, "growl"},
            {"Rest", 166, 0, 9, "rest"},
            {"Leer", 177, 0, 3, "leer"},
            {"Comet Punch", 162, 201, 5, "cometpunch"},
            {"Extreme Speed", 163, 130, 5, "extremespeed"},
            {"Tackle", 222, 163, 5, "tackle"},
            {"Egg Bomb", 237, 201, 5, "eggbomb"},
            {"Soft-Boiled", 167, 0, 9, "soft-boiled"},
            {"Slam", 169, 211, 5, "slam"},
            {"Tri Attack", 171, 81, 5, "triattack"},
            {"Take Down", 164, 189, 5, "takedown"},
            {"Swords Dance", 196, 0, 5, "swordsdance"},
            {"Supersonic", 179, 0, 3, "supersonic"},
            {"Sing", 178, 0, 3, "sing"},
            {"Recover", 180, 0, 9, "recover"},
            {"Petal Dance", 66, 156, 5, "petaldance"},
            {"Razor Leaf", 63, 118, 7, "razorleaf"},
            {"Spore", 68, 0, 9, "spore"},
            {"Synthesis", 70, 0, 5, "synthesis"},
            {"Mega Drain", 69, 165, 9, "megadrain"},
            {"Stun Spore", 67, 21, 3, "stunspore"},
            {"Solar Beam", 64, 227, 7, "solarbeam"},
            {"Bullet Seed", 217, 168, 7, "bulletseed"},
            {"Vine Whip", 65, 237, 5, "vinewhip"},
            {"Leech Seed", 39, 103, 9, "leechseed"},
            {"Fire Blast", 184, 179, 5, "fireblast"},
            {"Ember", 41, 109, 7, "ember"},
            {"Fire Punch", 44, 229, 5, "firepunch"},
            {"Fire Spin", 43, 97, 5, "firespin"},
            {"Lava Plume", 45, 132, 5, "lavaplume"},
            {"Flare Blitz", 42, 128, 5, "flareblitz"},
            {"Flame Wheel", 201, 57, 5, "flamewheel"},
            {"Flamethrower", 36, 94, 5, "flamethrower"},
            {"Heat Wave", 200, 123, 7, "heatwave"},
            {"Flame Charge", 47, 0, 5, "flamecharge"},
            {"Will-O-Wisp", 46, 19, 3, "will-o-wisp"},
            {"Rock Tomb", 194, 212, 5, "rocktomb"},
            {"Rock Throw", 188, 234, 5, "rockthrow"},
            {"Rollout", 189, 130, 5, "rollout"},
            {"Rock Blast", 191, 168, 7, "rockblast"},
            {"Rock Polish", 192, 0, 2, "rockpolish"},
            {"Sandstorm", 193, 117, 5, "sandstorm"},
            {"Stealth Rock", 190, 120, 5, "stealthrock"},
            {"Silver Wind", 128, 53, 5, "silverwind"},
            {"Rage Powder", 127, 0, 2, "ragepowder"},
            {"String Shot", 125, 118, 2, "stringshot"},
            {"Leech Life", 129, 185, 9, "leechlife"},
            {"Megahorn", 126, 513, 5, "megahorn"},
            {"Pin Missile", 123, 110, 7, "pinmissile"},
            {"Lunge", 124, 180, 5, "lunge"},
            {"U-turn", 130, 243, 5, "u-turn"},
            {"Volt Tackle", 220, 110, 6, "volttackle"},
            {"Thunder Shock", 56, 173, 5, "thundershock"},
            {"Electric Terrain", 61, 0, 5, "electricterrain"},
            {"Electroweb", 62, 0, 2, "electroweb"},
            {"Thunder", 38, 204, 5, "thunder"},
            {"Thunder Punch", 59, 194, 5, "thunderpunch"},
            {"Spark", 58, 81, 5, "spark"},
            {"Charge", 60, 0, 9, "charge"},
            {"Thunderbolt", 57, 80, 5, "thunderbolt"},
            {"Barrier", 116, 0, 5, "barrier"},
            {"Amnesia", 199, 0, 8, "amnesia"},
            {"Light Screen", 121, 0, 3, "lightscreen"},
            {"Agility", 115, 0, 2, "agility"},
            {"Psybeam", 112, 69, 7, "psybeam"},
            {"Psystrike", 122, 129, 5, "psystrike"},
            {"Psycho Cut", 119, 311, 5, "psychocut"},
            {"Psychic", 114, 121, 7, "psychic"},
            {"Hypnosis", 117, 0, 5, "hypnosis"},
            {"Zen Headbutt", 113, 370, 5, "zenheadbutt"},
            {"Teleport", 118, 0, 3, "teleport"},
            {"Meditate", 198, 0, 5, "meditate"},
            {"Aqua Ring", 54, 0, 9, "aquaring"},
            {"Aqua Jet", 55, 182, 5, "aquajet"},
            {"Bubble", 48, 68, 7, "bubble"},
            {"Hydro Pump", 50, 213, 5, "hydropump"},
            {"Withdraw", 52, 0, 5, "withdraw"},
            {"Surf", 37, 127, 5, "surf"},
            {"Waterfall", 49, 252, 5, "waterfall"},
            {"Whirlpool", 51, 94, 5, "whirlpool"},
            {"Dynamic Punch", 85, 87, 5, "dynamicpunch"},
            {"Bulk Up", 86, 0, 8, "bulkup"},
            {"Drain Punch", 87, 223, 9, "drainpunch"},
            {"Power-Up Punch", 80, 64, 5, "power-uppunch"},
            {"Close Combat", 239, 245, 5, "closecombat"},
            {"Rock Smash", 88, 29, 1, "rocksmash"},
            {"Cross Chop", 81, 273, 5, "crosschop"},
            {"Rolling Kick", 84, 156, 5, "rollingkick"},
            {"High Jump Kick", 83, 402, 5, "highjumpkick"},
            {"Submission", 82, 130, 5, "submission"},
            {"Dig", 101, 243, 5, "dig"},
            {"Mud Bomb", 98, 215, 5, "mudbomb"},
            {"Mud-Slap", 96, 56, 7, "mud-slap"},
            {"Bonemerang", 97, 131, 7, "bonemerang"},
            {"Earthquake", 100, 390, 5, "earthquake"},
            {"Spikes", 99, 221, 5, "spikes"},
            {"Shore Up", 102, 0, 9, "shoreup"},
            {"Venom Drench", 95, 118, 5, "venomdrench"},
            {"Poison Sting", 89, 107, 7, "poisonsting"},
            {"Toxic", 93, 59, 4, "toxic"},
            {"Poison Powder", 94, 67, 4, "poisonpowder"},
            {"Sludge Bomb", 90, 173, 5, "sludgebomb"},
            {"Smog", 91, 188, 5, "smog"},
            {"Acid Armor", 92, 0, 5, "acidarmor"},
            {"Hurricane", 108, 105, 5, "hurricane"},
            {"Drill Peck", 104, 321, 5, "drillpeck"},
            {"Sky Attack", 106, 125, 5, "skyattack"},
            {"Roost", 110, 0, 9, "roost"},
            {"Gust", 107, 61, 7, "gust"},
            {"Tailwind", 109, 0, 2, "tailwind"},
            {"Fly", 105, 243, 5, "fly"},
            {"Bounce", 223, 186, 5, "bounce"},
            {"Aerial Ace", 111, 124, 5, "aerialace"},
            {"Iron Tail", 150, 67, 5, "irontail"},
            {"Steel Wing", 149, 81, 5, "steelwing"},
            {"Metal Sound", 153, 0, 3, "metalsound"},
            {"Metal Claw", 151, 211, 5, "metalclaw"},
            {"Flash Cannon", 154, 170, 7, "flashcannon"},
            {"Iron Defense", 152, 0, 5, "irondefense"},
            {"Blizzard", 74, 52, 5, "blizzard"},
            {"Icy Wind", 79, 126, 7, "icywind"},
            {"Aurora Veil", 77, 0, 7, "auroraveil"},
            {"Ice Beam", 72, 133, 7, "icebeam"},
            {"Ice Punch", 75, 175, 5, "icepunch"},
            {"Icicle Crash", 73, 143, 5, "iciclecrash"},
            {"Sucker Punch", 145, 130, 5, "suckerpunch"},
            {"Crunch", 143, 370, 5, "crunch"},
            {"Flatter", 147, 0, 6, "flatter"},
            {"Night Slash", 144, 83, 5, "nightslash"},
            {"Taunt", 148, 0, 2, "taunt"},
            {"Nasty Plot", 146, 0, 5, "nastyplot"},
            {"Confuse Ray", 133, 0, 3, "confuseray"},
            {"Astonish", 135, 180, 5, "astonish"},
            {"Lick", 132, 233, 5, "lick"},
            {"Shadow Ball", 131, 63, 7, "shadowball"},
            {"Charm", 157, 0, 3, "charm"},
            {"Draining Kiss", 156, 165, 9, "drainingkiss"},
            {"Dazzling Gleam", 155, 146, 5, "dazzlinggleam"},
            {"Sweet Kiss", 158, 0, 3, "sweetkiss"},
            {"Play Rough", 160, 98, 5, "playrough"},
            {"Dragon Rush", 136, 141, 5, "dragonrush"},
            {"Dragon Claw", 138, 296, 5, "dragonclaw"},
            {"Outrage", 139, 104, 5, "outrage"},
            {"Dragon Pulse", 137, 188, 7, "dragonpulse"},
            {"Dragon Dance", 141, 0, 8, "dragondance"},
            {"Draco Meteor", 142, 377, 5, "dracometeor"},
            {"Twister", 140, 115, 7, "twister"},
            {"Base melee [bug]", 12, -1, -1, "type_bug"},
            {"Base ranged [bug]", 13, -1, -1, "type_bug"},
            {"Base melee [dark]", 32, -1, -1, "type_dark"},
            {"Base ranged [dark]", 33, -1, -1, "type_dark"},
            {"Base melee [dragon]", 30, -1, -1, "type_dragon"},
            {"Base ranged [dragon]", 31, -1, -1, "type_dragon"},
            {"Base melee [electric]", 24, -1, -1, "type_electric"},
            {"Base ranged [electric]", 25, -1, -1, "type_electric"},
            {"Base melee [fairy]", 34, -1, -1, "type_fairy"},
            {"Base ranged [fairy]", 35, -1, -1, "type_fairy"},
            {"Base melee [fighting]", 2, -1, -1, "type_fighting"},
            {"Base ranged [fighting]", 3, -1, -1, "type_fighting"},
            {"Base melee [fire]", 18, -1, -1, "type_fire"},
            {"Base ranged [fire]", 19, -1, -1, "type_fire"},
            {"Base melee [flying]", 4, -1, -1, "type_flying"},
            {"Base ranged [flying]", 5, -1, -1, "type_flying"},
            {"Base melee [ghost]", 14, -1, -1, "type_ghost"},
            {"Base ranged [ghost]", 15, -1, -1, "type_ghost"},
            {"Base melee [grass]", 22, -1, -1, "type_grass"},
            {"Base ranged [grass]", 23, -1, -1, "type_grass"},
            {"Base melee [ground]", 8, -1, -1, "type_ground"},
            {"Base ranged [ground]", 9, -1, -1, "type_ground"},
            {"Base melee [ice]", 28, -1, -1, "type_ice"},
            {"Base ranged [ice]", 29, -1, -1, "type_ice"},
            {"Base melee [normal]", 0, -1, -1, "type_normal"},
            {"Base ranged [normal]", 1, -1, -1, "type_normal"},
            {"Base melee [poison]", 6, -1, -1, "type_poison"},
            {"Base ranged [poison]", 7, -1, -1, "type_poison"},
            {"Base melee [psychic]", 26, -1, -1, "type_psychic"},
            {"Base ranged [psychic]", 27, -1, -1, "type_psychic"},
            {"Base melee [rock]", 10, -1, -1, "type_rock"},
            {"Base ranged [rock]", 11, -1, -1, "type_rock"},
            {"Base melee [steel]", 16, -1, -1, "type_steel"},
            {"Base ranged [steel]", 17, -1, -1, "type_steel"},
            {"Base melee [water]", 20, -1, -1, "type_water"},
            {"Base ranged [water]", 21, -1, -1, "type_water"}
        }};
        static constexpr std::array<std::array<PMove, 14>, 82> moveSets = {{
            {PMove::BaseMeleePoison, PMove::BaseMeleeGrass, PMove::VineWhip, PMove::Synthesis, PMove::Tackle, PMove::PetalDance, PMove::LeechSeed, PMove::TakeDown, PMove::PoisonPowder, PMove::Toxic, PMove::MegaDrain, PMove::SolarBeam},
            {PMove::BaseMeleeFire, PMove::FirePunch, PMove::Ember, PMove::FireSpin, PMove::Scratch, PMove::DragonClaw, PMove::MetalClaw, PMove::Flamethrower, PMove::FlareBlitz, PMove::FlameCharge, PMove::FireBlast},
            {PMove::BaseMeleeWater, PMove::Bubble, PMove::Whirlpool, PMove::Withdraw, PMove::Tackle, PMove::Waterfall, PMove::AquaJet, PMove::Surf, PMove::Blizzard, PMove::AquaRing, PMove::HydroPump},
            {PMove::BaseMeleeBug, PMove::BaseMeleeFlying, PMove::StringShot, PMove::TakeDown, PMove::Lunge, PMove::Tackle, PMove::Electroweb, PMove::Harden, PMove::IronDefense, PMove::RagePowder, PMove::SilverWind, PMove::UTurn},
            {PMove::BaseMeleeBug, PMove::BaseMeleePoison, PMove::StringShot, PMove::Tackle, PMove::Lunge, PMove::PoisonSting, PMove::Electroweb, PMove::Harden, PMove::IronDefense, PMove::Agility, PMove::AerialAce, PMove::PinMissile},
            {PMove::BaseRangedNormal, PMove::BaseRangedFlying, PMove::Gust, PMove::Whirlwind, PMove::Tailwind, PMove::Twister, PMove::Agility, PMove::Hurricane, PMove::MudSlap, PMove::SkyAttack, PMove::HeatWave, PMove::Roost},
            {PMove::BaseMeleeNormal, PMove::Tackle, PMove::TakeDown, PMove::Crunch, PMove::Scratch, PMove::FocusEnergy, PMove::FlameWheel, PMove::ZenHeadbutt, PMove::Taunt, PMove::IronTail, PMove::FurySwipes},
            {PMove::BaseMeleeNormal, PMove::BaseMeleeFlying, PMove::TakeDown, PMove::AerialAce, PMove::Growl, PMove::Fly, PMove::Leer, PMove::SteelWing, PMove::UTurn, PMove::Whirlwind, PMove::DrillPeck, PMove::TriAttack},
            {PMove::BaseRangedPoison, PMove::PoisonSting, PMove::MudBomb, PMove::RockTomb, PMove::MudSlap, PMove::Leer, PMove::SludgeBomb, PMove::SuckerPunch, PMove::Earthquake, PMove::Crunch, PMove::IronTail},
            {PMove::BaseMeleeElectric, PMove::IronTail, PMove::ThunderShock, PMove::Thunderbolt, PMove::Spark, PMove::VoltTackle, PMove::Agility, PMove::Thunder, PMove::ElectricTerrain, PMove::Charge, PMove::GigaImpact},
            {PMove::BaseMeleeGround, PMove::Scratch, PMove::MetalClaw, PMove::Dig, PMove::Sandstorm, PMove::Rollout, PMove::FurySwipes, PMove::Earthquake, PMove::SwordsDance, PMove::AerialAce, PMove::NightSlash},
            {PMove::BaseRangedPoison, PMove::BaseRangedGround, PMove::MudSlap, PMove::Growl, PMove::Flatter, PMove::FocusEnergy, PMove::Supersonic, PMove::PoisonSting, PMove::VenomDrench, PMove::SwordsDance, PMove::StealthRock, PMove::SludgeBomb},
            {PMove::BaseMeleePoison, PMove::BaseMeleeGround, PMove::TakeDown, PMove::Toxic, PMove::RockSmash, PMove::IronTail, PMove::Growl, PMove::Amnesia, PMove::RockTomb, PMove::Earthquake, PMove::Megahorn, PMove::Taunt},
            {PMove::BaseMeleeFairy, PMove::FollowMe, PMove::Flash, PMove::Rollout, PMove::TakeDown, PMove::LightScreen, PMove::Amnesia, PMove::SoftBoiled, PMove::Psychic, PMove::BellyDrum, PMove::DazzlingGleam},
            {PMove::BaseRangedFire, PMove::Flamethrower, PMove::Ember, PMove::Charm, PMove::Roar, PMove::FlameCharge, PMove::SolarBeam, PMove::ConfuseRay, PMove::HeatWave, PMove::WillOWisp, PMove::FireBlast},
            {PMove::BaseMeleeFairy, PMove::BaseMeleeNormal, PMove::TakeDown, PMove::Sing, PMove::MegaPunch, PMove::Flash, PMove::Rollout, PMove::Rest, PMove::SweetKiss, PMove::DynamicPunch, PMove::Bounce, PMove::PlayRough},
            {PMove::BaseRangedPoison, PMove::BaseRangedFlying, PMove::Taunt, PMove::Whirlwind, PMove::Gust, PMove::Supersonic, PMove::LeechLife, PMove::SludgeBomb, PMove::VenomDrench, PMove::Tailwind, PMove::Roost, PMove::NastyPlot},
            {PMove::BaseRangedPoison, PMove::BaseRangedGrass, PMove::PoisonPowder, PMove::StunSpore, PMove::Flash, PMove::PetalDance, PMove::Synthesis, PMove::BulletSeed, PMove::Charm, PMove::MegaDrain, PMove::SolarBeam, PMove::SwordsDance},
            {PMove::BaseRangedBug, PMove::BaseRangedGrass, PMove::LeechSeed, PMove::PoisonPowder, PMove::LightScreen, PMove::StunSpore, PMove::RagePowder, PMove::Spore, PMove::MetalClaw, PMove::Psybeam, PMove::Agility, PMove::BulletSeed},
            {PMove::BaseRangedBug, PMove::BaseRangedPoison, PMove::StringShot, PMove::PoisonPowder, PMove::Flash, PMove::StunSpore, PMove::Psybeam, PMove::Agility, PMove::SilverWind, PMove::Supersonic, PMove::Psychic, PMove::Gust},
            {PMove::BaseRangedGround, PMove::Dig, PMove::MudBomb, PMove::StealthRock, PMove::Growl, PMove::MudSlap, PMove::SuckerPunch, PMove::Earthquake, PMove::ShoreUp, PMove::RockTomb, PMove::RockThrow},
            {PMove::BaseMeleeNormal, PMove::Scratch, PMove::Taunt, PMove::FurySwipes, PMove::UTurn, PMove::Growl, PMove::Flail, PMove::PlayRough, PMove::NastyPlot, PMove::Roar, PMove::NightSlash},
            {PMove::BaseRangedWater, PMove::ConfuseRay, PMove::LightScreen, PMove::IcyWind, PMove::Whirlpool, PMove::Amnesia, PMove::MudBomb, PMove::HydroPump, PMove::Psychic, PMove::Psybeam, PMove::IceBeam},
            {PMove::BaseMeleeFighting, PMove::Taunt, PMove::Submission, PMove::Scratch, PMove::Leer, PMove::FurySwipes, PMove::MegaPunch, PMove::Meditate, PMove::CrossChop, PMove::CloseCombat, PMove::NightSlash},
            {PMove::BaseMeleeFire, PMove::Flamethrower, PMove::Ember, PMove::FlameCharge, PMove::Roar, PMove::FlameWheel, PMove::Crunch, PMove::Agility, PMove::FireBlast, PMove::FlareBlitz, PMove::ExtremeSpeed},
            {PMove::BaseMeleeWater, PMove::Bubble, PMove::Waterfall, PMove::Flail, PMove::Surf, PMove::Amnesia, PMove::MegaPunch, PMove::BulkUp, PMove::DynamicPunch, PMove::PowerUpPunch, PMove::IcePunch},
            {PMove::BaseRangedPsychic, PMove::Teleport, PMove::Psybeam, PMove::Flash, PMove::LightScreen, PMove::Psychic, PMove::Barrier, PMove::DazzlingGleam, PMove::Recover, PMove::ShadowBall, PMove::PsychoCut},
            {PMove::BaseMeleeFighting, PMove::RollingKick, PMove::Submission, PMove::BulkUp, PMove::RockSmash, PMove::MegaPunch, PMove::WorkUp, PMove::CrossChop, PMove::CloseCombat, PMove::PowerUpPunch, PMove::DynamicPunch},
            {PMove::BaseRangedPoison, PMove::BaseRangedGrass, PMove::RazorLeaf, PMove::Synthesis, PMove::SludgeBomb, PMove::BulletSeed, PMove::VineWhip, PMove::StunSpore, PMove::Slam, PMove::SwordsDance, PMove::SolarBeam, PMove::HyperBeam},
            {PMove::BaseRangedWater, PMove::BaseRangedPoison, PMove::Bubble, PMove::Barrier, PMove::SludgeBomb, PMove::Whirlpool, PMove::PoisonSting, PMove::HydroPump, PMove::IceBeam, PMove::Supersonic, PMove::IcyWind, PMove::ConfuseRay},
            {PMove::BaseMeleeRock, PMove::BaseMeleeGround, PMove::Flail, PMove::Dig, PMove::Tackle, PMove::Harden, PMove::StealthRock, PMove::Rollout, PMove::SelfDestruct, PMove::Earthquake, PMove::Explosion, PMove::RockPolish},
            {PMove::BaseMeleeFire, PMove::FlameCharge, PMove::Bounce, PMove::FireSpin, PMove::Stomp, PMove::Agility, PMove::FlameWheel, PMove::FlareBlitz, PMove::FireBlast, PMove::Megahorn, PMove::WillOWisp},
            {PMove::BaseMeleeWater, PMove::BaseMeleePsychic, PMove::Tackle, PMove::ZenHeadbutt, PMove::LightScreen, PMove::IcePunch, PMove::Growl, PMove::BellyDrum, PMove::Surf, PMove::Withdraw, PMove::Rest, PMove::Amnesia},
            {PMove::BaseRangedElectric, PMove::BaseRangedSteel, PMove::FlashCannon, PMove::MetalSound, PMove::Supersonic, PMove::Electroweb, PMove::Charge, PMove::LightScreen, PMove::ElectricTerrain, PMove::Thunder, PMove::Thunderbolt, PMove::Explosion},
            {PMove::BaseMeleeFlying, PMove::BaseMeleeNormal, PMove::SkyAttack, PMove::SuckerPunch, PMove::UTurn, PMove::Gust, PMove::SwordsDance, PMove::Tailwind, PMove::SteelWing, PMove::HeatWave, PMove::Roost, PMove::NightSlash},
            {PMove::BaseMeleeFlying, PMove::BaseMeleeNormal, PMove::TakeDown, PMove::Agility, PMove::DrillPeck, PMove::Growl, PMove::Flail, PMove::AerialAce, PMove::SwordsDance, PMove::WorkUp, PMove::TriAttack, PMove::Tailwind},
            {PMove::BaseMeleeWater, PMove::BaseMeleeIce, PMove::TakeDown, PMove::Blizzard, PMove::Surf, PMove::Lick, PMove::Growl, PMove::Slam, PMove::AuroraVeil, PMove::AquaJet, PMove::AquaRing, PMove::Rest},
            {PMove::BaseMeleePoison, PMove::Tackle, PMove::Toxic, PMove::Slam, PMove::AcidArmor, PMove::VenomDrench, PMove::PowerUpPunch, PMove::FirePunch, PMove::Taunt, PMove::RockTomb, PMove::Lick},
            {PMove::BaseRangedWater, PMove::BaseRangedIce, PMove::Withdraw, PMove::Bubble, PMove::IceBeam, PMove::Barrier, PMove::IronDefense, PMove::Spikes, PMove::RockBlast, PMove::Supersonic, PMove::IcyWind, PMove::IcicleCrash},
            {PMove::BaseMeleeGhost, PMove::BaseMeleePoison, PMove::Lick, PMove::Astonish, PMove::Smog, PMove::SuckerPunch, PMove::Toxic, PMove::ConfuseRay, PMove::Hypnosis, PMove::MegaDrain, PMove::ShadowBall, PMove::WillOWisp},
            {PMove::BaseRangedRock, PMove::BaseRangedGround, PMove::FlashCannon, PMove::StealthRock, PMove::Sandstorm, PMove::Harden, PMove::IronTail, PMove::RockSmash, PMove::RockThrow, PMove::RockPolish, PMove::Roar, PMove::RockTomb},
            {PMove::BaseRangedPsychic, PMove::Psybeam, PMove::Taunt, PMove::LightScreen, PMove::Barrier, PMove::Flash, PMove::Flatter, PMove::Psychic, PMove::ShadowBall, PMove::Meditate, PMove::Hypnosis},
            {PMove::BaseMeleeWater, PMove::Surf, PMove::Flail, PMove::Stomp, PMove::Harden, PMove::Leer, PMove::Slam, PMove::MetalClaw, PMove::SwordsDance, PMove::TakeDown, PMove::GigaImpact},
            {PMove::BaseMeleeElectric, PMove::SelfDestruct, PMove::Taunt, PMove::ThunderShock, PMove::Rollout, PMove::Tackle, PMove::Charge, PMove::SuckerPunch, PMove::LightScreen, PMove::Explosion, PMove::Spark},
            {PMove::BaseRangedGrass, PMove::BaseRangedPsychic, PMove::Psychic, PMove::SludgeBomb, PMove::LeechSeed, PMove::Flash, PMove::Synthesis, PMove::BulletSeed, PMove::EggBomb, PMove::Stomp, PMove::SolarBeam, PMove::StunSpore},
            {PMove::BaseMeleeGround, PMove::Bonemerang, PMove::Growl, PMove::Sandstorm, PMove::FocusEnergy, PMove::Leer, PMove::Outrage, PMove::RockTomb, PMove::BellyDrum, PMove::Earthquake, PMove::AerialAce},
            {PMove::BaseMeleeFighting, PMove::RollingKick, PMove::Submission, PMove::CloseCombat, PMove::FocusEnergy, PMove::BulkUp, PMove::Meditate, PMove::RockSmash, PMove::Bounce, PMove::HighJumpKick, PMove::SuckerPunch},
            {PMove::BaseMeleeFighting, PMove::DynamicPunch, PMove::CometPunch, PMove::MegaPunch, PMove::FirePunch, PMove::CloseCombat, PMove::ThunderPunch, PMove::IcePunch, PMove::PowerUpPunch, PMove::RockSmash, PMove::DrainPunch},
            {PMove::BaseMeleeNormal, PMove::Lick, PMove::Slam, PMove::Stomp, PMove::MegaPunch, PMove::IronTail, PMove::Amnesia, PMove::RockSmash, PMove::Rollout, PMove::BellyDrum, PMove::PowerUpPunch},
            {PMove::BaseRangedPoison, PMove::Flamethrower, PMove::Smog, PMove::SludgeBomb, PMove::SelfDestruct, PMove::LavaPlume, PMove::VenomDrench, PMove::Explosion, PMove::ShadowBall, PMove::Toxic, PMove::WillOWisp},
            {PMove::BaseMeleeGround, PMove::BaseMeleeRock, PMove::Roar, PMove::TakeDown, PMove::Stomp, PMove::Crunch, PMove::IronTail, PMove::Megahorn, PMove::Earthquake, PMove::RockSmash, PMove::DragonRush, PMove::RockPolish},
            {PMove::BaseMeleeNormal, PMove::TakeDown, PMove::MegaPunch, PMove::LightScreen, PMove::EggBomb, PMove::Sing, PMove::RockSmash, PMove::Flail, PMove::SoftBoiled, PMove::Charm, PMove::SweetKiss},
            {PMove::BaseMeleeGrass, PMove::VineWhip, PMove::Slam, PMove::LeechSeed, PMove::Synthesis, PMove::StunSpore, PMove::Amnesia, PMove::RagePowder, PMove::Substitute, PMove::MegaDrain, PMove::Rest},
            {PMove::BaseMeleeNormal, PMove::TakeDown, PMove::Outrage, PMove::Stomp, PMove::MegaPunch, PMove::FocusEnergy, PMove::Leer, PMove::RockTomb, PMove::Rest, PMove::PowerUpPunch, PMove::Crunch},
            {PMove::BaseRangedWater, PMove::Bubble, PMove::IcyWind, PMove::Agility, PMove::Whirlpool, PMove::Twister, PMove::FlashCannon, PMove::DragonPulse, PMove::IceBeam, PMove::DragonDance, PMove::HydroPump},
            {PMove::BaseMeleeWater, PMove::Splash, PMove::AquaJet, PMove::Surf, PMove::TakeDown, PMove::Flail, PMove::Bounce, PMove::Waterfall, PMove::Supersonic, PMove::Megahorn, PMove::Agility},
            {PMove::BaseRangedWater, PMove::BaseRangedPsychic, PMove::IcyWind, PMove::FlashCannon, PMove::IceBeam, PMove::Twister, PMove::Flash, PMove::ConfuseRay, PMove::Psychic, PMove::Blizzard, PMove::HyperBeam, PMove::HydroPump},
            {PMove::BaseRangedFairy, PMove::BaseRangedPsychic, PMove::Substitute, PMove::Taunt, PMove::Psychic, PMove::Barrier, PMove::Hypnosis, PMove::FollowMe, PMove::Meditate, PMove::LightScreen, PMove::Charm, PMove::NastyPlot},
            {PMove::BaseMeleeBug, PMove::BaseMeleeFlying, PMove::Lunge, PMove::SwordsDance, PMove::SteelWing, PMove::Tailwind, PMove::Agility, PMove::UTurn, PMove::AerialAce, PMove::NightSlash, PMove::RockSmash, PMove::SilverWind},
            {PMove::BaseRangedIce, PMove::BaseRangedPsychic, PMove::Psychic, PMove::Blizzard, PMove::IceBeam, PMove::Flash, PMove::Sing, PMove::Meditate, PMove::Psybeam, PMove::AuroraVeil, PMove::DrainingKiss, PMove::SweetKiss},
            {PMove::BaseMeleeElectric, PMove::Thunder, PMove::ThunderShock, PMove::Thunderbolt, PMove::Charge, PMove::ThunderPunch, PMove::Meditate, PMove::CrossChop, PMove::DynamicPunch, PMove::Electroweb, PMove::PowerUpPunch},
            {PMove::BaseMeleeFire, PMove::Flamethrower, PMove::Ember, PMove::FollowMe, PMove::FlareBlitz, PMove::LavaPlume, PMove::FireBlast, PMove::Smog, PMove::CrossChop, PMove::BellyDrum, PMove::WillOWisp},
            {PMove::BaseMeleeBug, PMove::TakeDown, PMove::Submission, PMove::Dig, PMove::FocusEnergy, PMove::BulkUp, PMove::Harden, PMove::RockTomb, PMove::RockSmash, PMove::CloseCombat, PMove::Earthquake},
            {PMove::BaseMeleeNormal, PMove::HyperBeam, PMove::Outrage, PMove::Blizzard, PMove::Earthquake, PMove::Thunderbolt, PMove::Flamethrower, PMove::ZenHeadbutt, PMove::GigaImpact, PMove::TakeDown, PMove::IronTail},
            {PMove::BaseMeleeWater, PMove::BaseMeleeFlying, PMove::Splash, PMove::Bounce, PMove::Tackle, PMove::Flail, PMove::DragonDance, PMove::Outrage, PMove::Waterfall, PMove::Crunch, PMove::HyperBeam, PMove::Taunt},
            {PMove::BaseRangedIce, PMove::BaseRangedWater, PMove::HydroPump, PMove::Whirlpool, PMove::Blizzard, PMove::IceBeam, PMove::Sing, PMove::Growl, PMove::AuroraVeil, PMove::IcicleCrash, PMove::Rest, PMove::IcyWind},
            {PMove::BaseMeleeNormal, PMove::Transform},
            {PMove::BaseMeleeNormal, PMove::Flail, PMove::TakeDown, PMove::Charm, PMove::Dig, PMove::Growl},
            {PMove::BaseMeleeWater, PMove::Flail, PMove::TakeDown, PMove::Charm, PMove::Dig, PMove::Growl, PMove::AcidArmor, PMove::HydroPump, PMove::AquaRing, PMove::Waterfall, PMove::Whirlpool},
            {PMove::BaseMeleeElectric, PMove::Flail, PMove::TakeDown, PMove::Charm, PMove::Dig, PMove::Growl, PMove::PinMissile, PMove::Agility, PMove::Spark, PMove::Thunder, PMove::Thunderbolt},
            {PMove::BaseMeleeFire, PMove::Flail, PMove::TakeDown, PMove::Charm, PMove::Dig, PMove::Growl, PMove::Flamethrower, PMove::LavaPlume, PMove::Ember, PMove::FireBlast, PMove::FlareBlitz},
            {PMove::BaseRangedNormal, PMove::Thunderbolt, PMove::Flamethrower, PMove::IceBeam, PMove::HyperBeam, PMove::Agility, PMove::Recover, PMove::TriAttack, PMove::IronTail, PMove::Psybeam, PMove::ShadowBall},
            {PMove::BaseRangedWater, PMove::BaseRangedRock, PMove::Bubble, PMove::IcyWind, PMove::Whirlpool, PMove::Spikes, PMove::Withdraw, PMove::RockBlast, PMove::HydroPump, PMove::IceBeam, PMove::RockPolish, PMove::Supersonic},
            {PMove::BaseMeleeWater, PMove::BaseMeleeRock, PMove::AquaJet, PMove::Withdraw, PMove::Waterfall, PMove::MetalSound, PMove::Surf, PMove::Sandstorm, PMove::RockTomb, PMove::SwordsDance, PMove::NightSlash, PMove::AerialAce},
            {PMove::BaseMeleeRock, PMove::BaseMeleeFlying, PMove::Crunch, PMove::TakeDown, PMove::Fly, PMove::Earthquake, PMove::SkyAttack, PMove::DragonClaw, PMove::RockTomb, PMove::Agility, PMove::Roost, PMove::Sandstorm},
            {PMove::BaseMeleeNormal, PMove::TakeDown, PMove::MegaPunch, PMove::Outrage, PMove::Earthquake, PMove::Harden, PMove::Rest, PMove::Amnesia, PMove::Rollout, PMove::BellyDrum, PMove::GigaImpact},
            {PMove::BaseRangedIce, PMove::BaseRangedFlying, PMove::SkyAttack, PMove::IceBeam, PMove::Blizzard, PMove::Agility, PMove::AuroraVeil, PMove::UTurn, PMove::Roost, PMove::SteelWing, PMove::Hurricane, PMove::IcyWind},
            {PMove::BaseRangedElectric, PMove::BaseRangedFlying, PMove::SkyAttack, PMove::Thunder, PMove::Charge, PMove::Thunderbolt, PMove::MetalSound, PMove::Agility, PMove::Roost, PMove::ThunderShock, PMove::DrillPeck, PMove::LightScreen},
            {PMove::BaseRangedFire, PMove::BaseRangedFlying, PMove::SkyAttack, PMove::Flamethrower, PMove::HeatWave, PMove::Leer, PMove::FireSpin, PMove::WillOWisp, PMove::Roost, PMove::Ember, PMove::LavaPlume, PMove::FireBlast},
            {PMove::BaseMeleeDragon, PMove::Agility, PMove::ExtremeSpeed, PMove::DragonRush, PMove::DragonDance, PMove::DragonPulse, PMove::Earthquake, PMove::Twister, PMove::Outrage, PMove::HyperBeam, PMove::DracoMeteor},
            {PMove::BaseRangedPsychic, PMove::Psychic, PMove::ShadowBall, PMove::Thunderbolt, PMove::BulkUp, PMove::Psystrike, PMove::Blizzard, PMove::Recover, PMove::PsychoCut, PMove::HyperBeam, PMove::GigaImpact},
            {PMove::BaseRangedPsychic, PMove::Psychic, PMove::FlashCannon, PMove::Amnesia, PMove::HeatWave, PMove::Thunder, PMove::Teleport, PMove::Recover, PMove::TriAttack, PMove::HyperBeam, PMove::GigaImpact},
        }};
        static constexpr std::array<MoveSet_t, 151> movesDB = {{
           {6, 0}, {9, 0}, {12, 0}, // bulbasaur, ivysaur, venusaur
           {5, 1}, {8, 1}, {11, 1}, // Charmander, Charmeleon, Charizard
           {5, 2}, {8, 2}, {11, 2}, // Squirtle, Wartortle, Blastoise
           {6, 3}, {9, 3}, {12, 3}, // Caterpie, Metapod, Butterfree
           {6, 4}, {9, 4}, {12, 4}, // Weedle, Kakuna, Beedrill
           {6, 5}, {9, 5}, {12, 5}, // Pidgey, Pidgeotto, Pidgeot
           {6, 6}, {11, 6}, // Rattata, Raticate
           {7, 7}, {12, 7}, // Spearow, Fearow
           {6, 8}, {11, 8}, // Ekans, Arbok
           {6, 9}, {11, 9}, // Pikachu, Raichu
           {6, 10}, {11, 10}, // Sandshrew, Sandslash
           {6, 11}, {9, 11}, {12, 11}, // Nidoran ♀, Nidorina, Nidoqueen
           {6, 12}, {9, 12}, {12, 12}, // Nidoran ♂, Nidorino, Nidoking
           {6, 13}, {11, 13}, // Clefairy, Clefable
           {6, 14}, {11, 14}, // Vulpix, Ninetales
           {7, 15}, {12, 15}, // Jigglypuff, Wigglytuff
           {7, 16}, {12, 16}, // Zubat, Golbat
           {6, 17}, {9, 17}, {12, 17}, // Oddish, Gloom, Vileplume
           {7, 18}, {12, 18}, // Paras, Parasect
           {7, 19}, {12, 19}, // Venonat, Venomoth
           {6, 20}, {11, 20}, // Diglett, Dugtrio
           {6, 21}, {11, 21}, // Meowth, Persian
           {6, 22}, {11, 22}, // Psyduck, Golduck
           {6, 23}, {11, 23}, // Mankey, Primeape
           {6, 24}, {11, 24}, // Growlithe, Arcanine
           {5, 25}, {8, 25}, {11, 25}, // Poliwag, Poliwhirl, Poliwrath
           {5, 26}, {8, 26}, {11, 26}, // Abra, Kadabra, Alakazam
           {5, 27}, {8, 27}, {11, 27}, // Machop, Machoke, Machamp
           {6, 28}, {9, 28}, {12, 28}, // Bellsprout, Weepinbell, Victreebel
           {7, 29}, {12, 29}, // Tentacool, Tentacruel
           {6, 30}, {9, 30}, {12, 30}, // Geodude, Graveler, Golem
           {6, 31}, {11, 31}, // Ponyta, Rapidash
           {7, 32}, {12, 32}, // Slowpoke, Slowbro
           {7, 33}, {12, 33}, // Magnemite, Magneton
           {12, 34}, // Farfetch’d
           {7, 35}, {12, 35}, // Doduo, Dodrio
           {7, 36}, {12, 36}, // Seel, Dewgong
           {6, 37}, {11, 37}, // Grimer, Muk
           {7, 38}, {12, 38}, // Shellder, Cloyster
           {6, 39}, {9, 39}, {12, 39}, // Gastly, Haunter, Gengar
           {12, 40}, // Onix
           {6, 41}, {11, 41}, // Drowzee, Hypno
           {6, 42}, {11, 42}, // Krabby, Kingler
           {6, 43}, {11, 43}, // Voltorb, Electrode
           {7, 44}, {12, 44}, // Exeggcute, Exeggutor
           {6, 45}, {11, 45}, // Cubone, Marowak
           {11, 46}, // Hitmonlee
           {11, 47}, // Hitmonchan
           {11, 48}, // Lickitung
           {6, 49}, {11, 49}, // Koffing, Weezing
           {7, 50}, {12, 50}, // Rhyhorn, Rhydon
           {11, 51}, // Chansey
           {11, 52}, // Tangela
           {11, 53}, // Kangaskhan
           {7, 54}, {12, 54}, // Horsea, Seadra
           {6, 55}, {11, 55}, // Goldeen, Seaking
           {7, 56}, {12, 56}, // Staryu, Starmie
           {12, 57}, // Mime
           {12, 58}, // Scyther
           {12, 59}, // Jynx
           {11, 60}, // Electabuzz
           {11, 61}, // Magmar
           {11, 62}, // Pinsir
           {11, 63}, // Tauros
           {7, 64}, {12, 64}, // Magikarp, Gyarados
           {12, 65}, // Lapras
           {2, 66}, // Ditto
           {6, 67}, // Eevee
           {11, 68}, // Vaporeon
           {11, 69}, // Jolteon
           {11, 70}, // Flareon
           {11, 71}, // Porygon
           {7, 72}, {12, 72}, // Omanyte, Omastar
           {7, 73}, {12, 73}, // Kabuto, Kabutops
           {12, 74}, // Aerodactyl
           {11, 75}, // Snorlax
           {12, 76}, // Articuno
           {12, 77}, // Zapdos
           {12, 78}, // Moltres
           {5, 79}, {8, 79}, {11, 79}, // Dratini, Dragonair, Dragonite
           {11, 80}, // Mewtwo
           {11, 81} // Mew
        }};

        QVBoxLayout *skillsLyt = nullptr;
        QCheckBox *moveFilter = nullptr;
        QList<QSpinBox *> slotIndexList;
        QList<QComboBox *> skillIDList;
        int monsterNo;
        std::shared_ptr<SaveCharacterPoteintialData> potentialData;

        void addSkillItem(QComboBox *combo, const Move_t &move) const;
        void setSkillCombos(bool filter) const;

    public:
        PotentialSkillDataEditor();

        void setData(const std::shared_ptr<SaveCharacterPoteintialData> &data, int dexNo);
        void updateMonsterNo(int dexNo);
        void refresh() const;
        void apply() const;

    private slots:
        void onMoveFilterChanged(Qt::CheckState state) const;
    };
}
