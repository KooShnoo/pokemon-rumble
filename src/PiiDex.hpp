#pragma once

#include "macros.h"

enum PiiSpecies {
    _NULL_SPECIES,
    BULBASAUR,
    IVYSAUR,
    VENUSAUR,
    CHARMANDER,
    CHARMELEON,
    CHARIZARD,
    SQUIRTLE,
    WARTORTLE,
    BLASTOISE,
    CATERPIE,
    METAPOD,
    BUTTERFREE,
    WEEDLE,
    KAKUNA,
    BEEDRILL,
    PIDGEY,
    PIDGEOTTO,
    PIDGEOT,
    RATTATA,
    RATICATE,
    SPEAROW,
    FEAROW,
    EKANS,
    ARBOK,
    PIKACHU,
    RAICHU,
    SANDSHREW,
    SANDSLASH,
    NIDORAN_F,
    NIDORINA,
    NIDOQUEEN,
    NIDORAN_M,
    NIDORINO,
    NIDOKING,
    CLEFAIRY,
    CLEFABLE,
    VULPIX,
    NINETALES,
    JIGGLYPUFF,
    WIGGLYTUFF,
    ZUBAT,
    GOLBAT,
    ODDISH,
    GLOOM,
    VILEPLUME,
    PARAS,
    PARASECT,
    VENONAT,
    VENOMOTH,
    DIGLETT,
    DUGTRIO,
    MEOWTH,
    PERSIAN,
    PSYDUCK,
    GOLDUCK,
    MANKEY,
    PRIMEAPE,
    GROWLITHE,
    ARCANINE,
    POLIWAG,
    POLIWHIRL,
    POLIWRATH,
    ABRA,
    KADABRA,
    ALAKAZAM,
    MACHOP,
    MACHOKE,
    MACHAMP,
    BELLSPROUT,
    WEEPINBELL,
    VICTREEBEL,
    TENTACOOL,
    TENTACRUEL,
    GEODUDE,
    GRAVELER,
    GOLEM,
    PONYTA,
    RAPIDASH,
    SLOWPOKE,
    SLOWBRO,
    MAGNEMITE,
    MAGNETON,
    FARFETCH_D,
    DODUO,
    DODRIO,
    SEEL,
    DEWGONG,
    GRIMER,
    MUK,
    SHELLDER,
    CLOYSTER,
    GASTLY,
    HAUNTER,
    GENGAR,
    ONIX,
    DROWZEE,
    HYPNO,
    KRABBY,
    KINGLER,
    VOLTORB,
    ELECTRODE,
    EXEGGCUTE,
    EXEGGUTOR,
    CUBONE,
    MAROWAK,
    HITMONLEE,
    HITMONCHAN,
    LICKITUNG,
    KOFFING,
    WEEZING,
    RHYHORN,
    RHYDON,
    CHANSEY,
    TANGELA,
    KANGASKHAN,
    HORSEA,
    SEADRA,
    GOLDEEN,
    SEAKING,
    STARYU,
    STARMIE,
    MR_MIME,
    SCYTHER,
    JYNX,
    ELECTABUZZ,
    MAGMAR,
    PINSIR,
    TAUROS,
    MAGIKARP,
    GYARADOS,
    LAPRAS,
    DITTO,
    EEVEE,
    VAPOREON,
    JOLTEON,
    FLAREON,
    PORYGON,
    OMANYTE,
    OMASTAR,
    KABUTO,
    KABUTOPS,
    AERODACTYL,
    SNORLAX,
    ARTICUNO,
    ZAPDOS,
    MOLTRES,
    DRATINI,
    DRAGONAIR,
    DRAGONITE,
    MEWTWO,
    MEW,
    CHIKORITA,
    BAYLEEF,
    MEGANIUM,
    CYNDAQUIL,
    QUILAVA,
    TYPHLOSION,
    TOTODILE,
    CROCONAW,
    FERALIGATR,
    SENTRET,
    FURRET,
    HOOTHOOT,
    NOCTOWL,
    LEDYBA,
    LEDIAN,
    SPINARAK,
    ARIADOS,
    CROBAT,
    CHINCHOU,
    LANTURN,
    PICHU,
    CLEFFA,
    IGGLYBUFF,
    TOGEPI,
    TOGETIC,
    NATU,
    XATU,
    MAREEP,
    FLAAFFY,
    AMPHAROS,
    BELLOSSOM,
    MARILL,
    AZUMARILL,
    SUDOWOODO,
    POLITOED,
    HOPPIP,
    SKIPLOOM,
    JUMPLUFF,
    AIPOM,
    SUNKERN,
    SUNFLORA,
    YANMA,
    WOOPER,
    QUAGSIRE,
    ESPEON,
    UMBREON,
    MURKROW,
    SLOWKING,
    MISDREAVUS,
    UNOWN,
    WOBBUFFET,
    GIRAFARIG,
    PINECO,
    FORRETRESS,
    DUNSPARCE,
    GLIGAR,
    STEELIX,
    SNUBBULL,
    GRANBULL,
    QWILFISH,
    SCIZOR,
    SHUCKLE,
    HERACROSS,
    SNEASEL,
    TEDDIURSA,
    URSARING,
    SLUGMA,
    MAGCARGO,
    SWINUB,
    PILOSWINE,
    CORSOLA,
    REMORAID,
    OCTILLERY,
    DELIBIRD,
    MANTINE,
    SKARMORY,
    HOUNDOUR,
    HOUNDOOM,
    KINGDRA,
    PHANPY,
    DONPHAN,
    PORYGON2,
    STANTLER,
    SMEARGLE,
    TYROGUE,
    HITMONTOP,
    SMOOCHUM,
    ELEKID,
    MAGBY,
    MILTANK,
    BLISSEY,
    RAIKOU,
    ENTEI,
    SUICUNE,
    LARVITAR,
    PUPITAR,
    TYRANITAR,
    LUGIA,
    HO_OH,
    CELEBI,
    TREECKO,
    GROVYLE,
    SCEPTILE,
    TORCHIC,
    COMBUSKEN,
    BLAZIKEN,
    MUDKIP,
    MARSHTOMP,
    SWAMPERT,
    POOCHYENA,
    MIGHTYENA,
    ZIGZAGOON,
    LINOONE,
    WURMPLE,
    SILCOON,
    BEAUTIFLY,
    CASCOON,
    DUSTOX,
    LOTAD,
    LOMBRE,
    LUDICOLO,
    SEEDOT,
    NUZLEAF,
    SHIFTRY,
    TAILLOW,
    SWELLOW,
    WINGULL,
    PELIPPER,
    RALTS,
    KIRLIA,
    GARDEVOIR,
    SURSKIT,
    MASQUERAIN,
    SHROOMISH,
    BRELOOM,
    SLAKOTH,
    VIGOROTH,
    SLAKING,
    NINCADA,
    NINJASK,
    SHEDINJA,
    WHISMUR,
    LOUDRED,
    EXPLOUD,
    MAKUHITA,
    HARIYAMA,
    AZURILL,
    NOSEPASS,
    SKITTY,
    DELCATTY,
    SABLEYE,
    MAWILE,
    ARON,
    LAIRON,
    AGGRON,
    MEDITITE,
    MEDICHAM,
    ELECTRIKE,
    MANECTRIC,
    PLUSLE,
    MINUN,
    VOLBEAT,
    ILLUMISE,
    ROSELIA,
    GULPIN,
    SWALOT,
    CARVANHA,
    SHARPEDO,
    WAILMER,
    WAILORD,
    NUMEL,
    CAMERUPT,
    TORKOAL,
    SPOINK,
    GRUMPIG,
    SPINDA,
    TRAPINCH,
    VIBRAVA,
    FLYGON,
    CACNEA,
    CACTURNE,
    SWABLU,
    ALTARIA,
    ZANGOOSE,
    SEVIPER,
    LUNATONE,
    SOLROCK,
    BARBOACH,
    WHISCASH,
    CORPHISH,
    CRAWDAUNT,
    BALTOY,
    CLAYDOL,
    LILEEP,
    CRADILY,
    ANORITH,
    ARMALDO,
    FEEBAS,
    MILOTIC,
    CASTFORM,
    KECLEON,
    SHUPPET,
    BANETTE,
    DUSKULL,
    DUSCLOPS,
    TROPIUS,
    CHIMECHO,
    ABSOL,
    WYNAUT,
    SNORUNT,
    GLALIE,
    SPHEAL,
    SEALEO,
    WALREIN,
    CLAMPERL,
    HUNTAIL,
    GOREBYSS,
    RELICANTH,
    LUVDISC,
    BAGON,
    SHELGON,
    SALAMENCE,
    BELDUM,
    METANG,
    METAGROSS,
    REGIROCK,
    REGICE,
    REGISTEEL,
    LATIAS,
    LATIOS,
    KYOGRE,
    GROUDON,
    RAYQUAZA,
    JIRACHI,
    DEOXYS,
    TURTWIG,
    GROTLE,
    TORTERRA,
    CHIMCHAR,
    MONFERNO,
    INFERNAPE,
    PIPLUP,
    PRINPLUP,
    EMPOLEON,
    STARLY,
    STARAVIA,
    STARAPTOR,
    BIDOOF,
    BIBAREL,
    KRICKETOT,
    KRICKETUNE,
    SHINX,
    LUXIO,
    LUXRAY,
    BUDEW,
    ROSERADE,
    CRANIDOS,
    RAMPARDOS,
    SHIELDON,
    BASTIODON,
    BURMY,
    WORMADAM,
    MOTHIM,
    COMBEE,
    VESPIQUEN,
    PACHIRISU,
    BUIZEL,
    FLOATZEL,
    CHERUBI,
    CHERRIM,
    SHELLOS,
    GASTRODON,
    AMBIPOM,
    DRIFLOON,
    DRIFBLIM,
    BUNEARY,
    LOPUNNY,
    MISMAGIUS,
    HONCHKROW,
    GLAMEOW,
    PURUGLY,
    CHINGLING,
    STUNKY,
    SKUNTANK,
    BRONZOR,
    BRONZONG,
    BONSLY,
    MIME_JR,
    HAPPINY,
    CHATOT,
    SPIRITOMB,
    GIBLE,
    GABITE,
    GARCHOMP,
    MUNCHLAX,
    RIOLU,
    LUCARIO,
    HIPPOPOTAS,
    HIPPOWDON,
    SKORUPI,
    DRAPION,
    CROAGUNK,
    TOXICROAK,
    CARNIVINE,
    FINNEON,
    LUMINEON,
    MANTYKE,
    SNOVER,
    ABOMASNOW,
    WEAVILE,
    MAGNEZONE,
    LICKILICKY,
    RHYPERIOR,
    TANGROWTH,
    ELECTIVIRE,
    MAGMORTAR,
    TOGEKISS,
    YANMEGA,
    LEAFEON,
    GLACEON,
    GLISCOR,
    MAMOSWINE,
    PORYGON_Z,
    GALLADE,
    PROBOPASS,
    DUSKNOIR,
    FROSLASS,
    ROTOM,
    UXIE,
    MESPRIT,
    AZELF,
    DIALGA,
    PALKIA,
    HEATRAN,
    REGIGIGAS,
    GIRATINA,
    CRESSELIA,
    PHIONE,
    MANAPHY,
    DARKRAI,
    SHAYMIN,
    ARCEUS,
    EGG,
    BAD_EGG,
    NIDORAN
};

enum PiiType {
    NORMAL,
    FIGHTING,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    STEEL,
    UNKNOWN, // ???
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCHIC,
    ICE,
    DRAGON,
    DARK,
};

static_assert(BULBASAUR == 1);
static_assert(IVYSAUR == 2);
static_assert(VENUSAUR == 3);
static_assert(CHARMANDER == 4);
static_assert(CHARMELEON == 5);
static_assert(CHARIZARD == 6);
static_assert(SQUIRTLE == 7);
static_assert(WARTORTLE == 8);
static_assert(BLASTOISE == 9);
static_assert(CATERPIE == 10);
static_assert(METAPOD == 11);
static_assert(BUTTERFREE == 12);
static_assert(WEEDLE == 13);
static_assert(KAKUNA == 14);
static_assert(BEEDRILL == 15);
static_assert(PIDGEY == 16);
static_assert(PIDGEOTTO == 17);
static_assert(PIDGEOT == 18);
static_assert(RATTATA == 19);
static_assert(RATICATE == 20);
static_assert(SPEAROW == 21);
static_assert(FEAROW == 22);
static_assert(EKANS == 23);
static_assert(ARBOK == 24);
static_assert(PIKACHU == 25);
static_assert(RAICHU == 26);
static_assert(SANDSHREW == 27);
static_assert(SANDSLASH == 28);
static_assert(NIDORAN_F == 29);
static_assert(NIDORINA == 30);
static_assert(NIDOQUEEN == 31);
static_assert(NIDORAN_M == 32);
static_assert(NIDORINO == 33);
static_assert(NIDOKING == 34);
static_assert(CLEFAIRY == 35);
static_assert(CLEFABLE == 36);
static_assert(VULPIX == 37);
static_assert(NINETALES == 38);
static_assert(JIGGLYPUFF == 39);
static_assert(WIGGLYTUFF == 40);
static_assert(ZUBAT == 41);
static_assert(GOLBAT == 42);
static_assert(ODDISH == 43);
static_assert(GLOOM == 44);
static_assert(VILEPLUME == 45);
static_assert(PARAS == 46);
static_assert(PARASECT == 47);
static_assert(VENONAT == 48);
static_assert(VENOMOTH == 49);
static_assert(DIGLETT == 50);
static_assert(DUGTRIO == 51);
static_assert(MEOWTH == 52);
static_assert(PERSIAN == 53);
static_assert(PSYDUCK == 54);
static_assert(GOLDUCK == 55);
static_assert(MANKEY == 56);
static_assert(PRIMEAPE == 57);
static_assert(GROWLITHE == 58);
static_assert(ARCANINE == 59);
static_assert(POLIWAG == 60);
static_assert(POLIWHIRL == 61);
static_assert(POLIWRATH == 62);
static_assert(ABRA == 63);
static_assert(KADABRA == 64);
static_assert(ALAKAZAM == 65);
static_assert(MACHOP == 66);
static_assert(MACHOKE == 67);
static_assert(MACHAMP == 68);
static_assert(BELLSPROUT == 69);
static_assert(WEEPINBELL == 70);
static_assert(VICTREEBEL == 71);
static_assert(TENTACOOL == 72);
static_assert(TENTACRUEL == 73);
static_assert(GEODUDE == 74);
static_assert(GRAVELER == 75);
static_assert(GOLEM == 76);
static_assert(PONYTA == 77);
static_assert(RAPIDASH == 78);
static_assert(SLOWPOKE == 79);
static_assert(SLOWBRO == 80);
static_assert(MAGNEMITE == 81);
static_assert(MAGNETON == 82);
static_assert(FARFETCH_D == 83);
static_assert(DODUO == 84);
static_assert(DODRIO == 85);
static_assert(SEEL == 86);
static_assert(DEWGONG == 87);
static_assert(GRIMER == 88);
static_assert(MUK == 89);
static_assert(SHELLDER == 90);
static_assert(CLOYSTER == 91);
static_assert(GASTLY == 92);
static_assert(HAUNTER == 93);
static_assert(GENGAR == 94);
static_assert(ONIX == 95);
static_assert(DROWZEE == 96);
static_assert(HYPNO == 97);
static_assert(KRABBY == 98);
static_assert(KINGLER == 99);
static_assert(VOLTORB == 100);
static_assert(ELECTRODE == 101);
static_assert(EXEGGCUTE == 102);
static_assert(EXEGGUTOR == 103);
static_assert(CUBONE == 104);
static_assert(MAROWAK == 105);
static_assert(HITMONLEE == 106);
static_assert(HITMONCHAN == 107);
static_assert(LICKITUNG == 108);
static_assert(KOFFING == 109);
static_assert(WEEZING == 110);
static_assert(RHYHORN == 111);
static_assert(RHYDON == 112);
static_assert(CHANSEY == 113);
static_assert(TANGELA == 114);
static_assert(KANGASKHAN == 115);
static_assert(HORSEA == 116);
static_assert(SEADRA == 117);
static_assert(GOLDEEN == 118);
static_assert(SEAKING == 119);
static_assert(STARYU == 120);
static_assert(STARMIE == 121);
static_assert(MR_MIME == 122);
static_assert(SCYTHER == 123);
static_assert(JYNX == 124);
static_assert(ELECTABUZZ == 125);
static_assert(MAGMAR == 126);
static_assert(PINSIR == 127);
static_assert(TAUROS == 128);
static_assert(MAGIKARP == 129);
static_assert(GYARADOS == 130);
static_assert(LAPRAS == 131);
static_assert(DITTO == 132);
static_assert(EEVEE == 133);
static_assert(VAPOREON == 134);
static_assert(JOLTEON == 135);
static_assert(FLAREON == 136);
static_assert(PORYGON == 137);
static_assert(OMANYTE == 138);
static_assert(OMASTAR == 139);
static_assert(KABUTO == 140);
static_assert(KABUTOPS == 141);
static_assert(AERODACTYL == 142);
static_assert(SNORLAX == 143);
static_assert(ARTICUNO == 144);
static_assert(ZAPDOS == 145);
static_assert(MOLTRES == 146);
static_assert(DRATINI == 147);
static_assert(DRAGONAIR == 148);
static_assert(DRAGONITE == 149);
static_assert(MEWTWO == 150);
static_assert(MEW == 151);
static_assert(CHIKORITA == 152);
static_assert(BAYLEEF == 153);
static_assert(MEGANIUM == 154);
static_assert(CYNDAQUIL == 155);
static_assert(QUILAVA == 156);
static_assert(TYPHLOSION == 157);
static_assert(TOTODILE == 158);
static_assert(CROCONAW == 159);
static_assert(FERALIGATR == 160);
static_assert(SENTRET == 161);
static_assert(FURRET == 162);
static_assert(HOOTHOOT == 163);
static_assert(NOCTOWL == 164);
static_assert(LEDYBA == 165);
static_assert(LEDIAN == 166);
static_assert(SPINARAK == 167);
static_assert(ARIADOS == 168);
static_assert(CROBAT == 169);
static_assert(CHINCHOU == 170);
static_assert(LANTURN == 171);
static_assert(PICHU == 172);
static_assert(CLEFFA == 173);
static_assert(IGGLYBUFF == 174);
static_assert(TOGEPI == 175);
static_assert(TOGETIC == 176);
static_assert(NATU == 177);
static_assert(XATU == 178);
static_assert(MAREEP == 179);
static_assert(FLAAFFY == 180);
static_assert(AMPHAROS == 181);
static_assert(BELLOSSOM == 182);
static_assert(MARILL == 183);
static_assert(AZUMARILL == 184);
static_assert(SUDOWOODO == 185);
static_assert(POLITOED == 186);
static_assert(HOPPIP == 187);
static_assert(SKIPLOOM == 188);
static_assert(JUMPLUFF == 189);
static_assert(AIPOM == 190);
static_assert(SUNKERN == 191);
static_assert(SUNFLORA == 192);
static_assert(YANMA == 193);
static_assert(WOOPER == 194);
static_assert(QUAGSIRE == 195);
static_assert(ESPEON == 196);
static_assert(UMBREON == 197);
static_assert(MURKROW == 198);
static_assert(SLOWKING == 199);
static_assert(MISDREAVUS == 200);
static_assert(UNOWN == 201);
static_assert(WOBBUFFET == 202);
static_assert(GIRAFARIG == 203);
static_assert(PINECO == 204);
static_assert(FORRETRESS == 205);
static_assert(DUNSPARCE == 206);
static_assert(GLIGAR == 207);
static_assert(STEELIX == 208);
static_assert(SNUBBULL == 209);
static_assert(GRANBULL == 210);
static_assert(QWILFISH == 211);
static_assert(SCIZOR == 212);
static_assert(SHUCKLE == 213);
static_assert(HERACROSS == 214);
static_assert(SNEASEL == 215);
static_assert(TEDDIURSA == 216);
static_assert(URSARING == 217);
static_assert(SLUGMA == 218);
static_assert(MAGCARGO == 219);
static_assert(SWINUB == 220);
static_assert(PILOSWINE == 221);
static_assert(CORSOLA == 222);
static_assert(REMORAID == 223);
static_assert(OCTILLERY == 224);
static_assert(DELIBIRD == 225);
static_assert(MANTINE == 226);
static_assert(SKARMORY == 227);
static_assert(HOUNDOUR == 228);
static_assert(HOUNDOOM == 229);
static_assert(KINGDRA == 230);
static_assert(PHANPY == 231);
static_assert(DONPHAN == 232);
static_assert(PORYGON2 == 233);
static_assert(STANTLER == 234);
static_assert(SMEARGLE == 235);
static_assert(TYROGUE == 236);
static_assert(HITMONTOP == 237);
static_assert(SMOOCHUM == 238);
static_assert(ELEKID == 239);
static_assert(MAGBY == 240);
static_assert(MILTANK == 241);
static_assert(BLISSEY == 242);
static_assert(RAIKOU == 243);
static_assert(ENTEI == 244);
static_assert(SUICUNE == 245);
static_assert(LARVITAR == 246);
static_assert(PUPITAR == 247);
static_assert(TYRANITAR == 248);
static_assert(LUGIA == 249);
static_assert(HO_OH == 250);
static_assert(CELEBI == 251);
static_assert(TREECKO == 252);
static_assert(GROVYLE == 253);
static_assert(SCEPTILE == 254);
static_assert(TORCHIC == 255);
static_assert(COMBUSKEN == 256);
static_assert(BLAZIKEN == 257);
static_assert(MUDKIP == 258);
static_assert(MARSHTOMP == 259);
static_assert(SWAMPERT == 260);
static_assert(POOCHYENA == 261);
static_assert(MIGHTYENA == 262);
static_assert(ZIGZAGOON == 263);
static_assert(LINOONE == 264);
static_assert(WURMPLE == 265);
static_assert(SILCOON == 266);
static_assert(BEAUTIFLY == 267);
static_assert(CASCOON == 268);
static_assert(DUSTOX == 269);
static_assert(LOTAD == 270);
static_assert(LOMBRE == 271);
static_assert(LUDICOLO == 272);
static_assert(SEEDOT == 273);
static_assert(NUZLEAF == 274);
static_assert(SHIFTRY == 275);
static_assert(TAILLOW == 276);
static_assert(SWELLOW == 277);
static_assert(WINGULL == 278);
static_assert(PELIPPER == 279);
static_assert(RALTS == 280);
static_assert(KIRLIA == 281);
static_assert(GARDEVOIR == 282);
static_assert(SURSKIT == 283);
static_assert(MASQUERAIN == 284);
static_assert(SHROOMISH == 285);
static_assert(BRELOOM == 286);
static_assert(SLAKOTH == 287);
static_assert(VIGOROTH == 288);
static_assert(SLAKING == 289);
static_assert(NINCADA == 290);
static_assert(NINJASK == 291);
static_assert(SHEDINJA == 292);
static_assert(WHISMUR == 293);
static_assert(LOUDRED == 294);
static_assert(EXPLOUD == 295);
static_assert(MAKUHITA == 296);
static_assert(HARIYAMA == 297);
static_assert(AZURILL == 298);
static_assert(NOSEPASS == 299);
static_assert(SKITTY == 300);
static_assert(DELCATTY == 301);
static_assert(SABLEYE == 302);
static_assert(MAWILE == 303);
static_assert(ARON == 304);
static_assert(LAIRON == 305);
static_assert(AGGRON == 306);
static_assert(MEDITITE == 307);
static_assert(MEDICHAM == 308);
static_assert(ELECTRIKE == 309);
static_assert(MANECTRIC == 310);
static_assert(PLUSLE == 311);
static_assert(MINUN == 312);
static_assert(VOLBEAT == 313);
static_assert(ILLUMISE == 314);
static_assert(ROSELIA == 315);
static_assert(GULPIN == 316);
static_assert(SWALOT == 317);
static_assert(CARVANHA == 318);
static_assert(SHARPEDO == 319);
static_assert(WAILMER == 320);
static_assert(WAILORD == 321);
static_assert(NUMEL == 322);
static_assert(CAMERUPT == 323);
static_assert(TORKOAL == 324);
static_assert(SPOINK == 325);
static_assert(GRUMPIG == 326);
static_assert(SPINDA == 327);
static_assert(TRAPINCH == 328);
static_assert(VIBRAVA == 329);
static_assert(FLYGON == 330);
static_assert(CACNEA == 331);
static_assert(CACTURNE == 332);
static_assert(SWABLU == 333);
static_assert(ALTARIA == 334);
static_assert(ZANGOOSE == 335);
static_assert(SEVIPER == 336);
static_assert(LUNATONE == 337);
static_assert(SOLROCK == 338);
static_assert(BARBOACH == 339);
static_assert(WHISCASH == 340);
static_assert(CORPHISH == 341);
static_assert(CRAWDAUNT == 342);
static_assert(BALTOY == 343);
static_assert(CLAYDOL == 344);
static_assert(LILEEP == 345);
static_assert(CRADILY == 346);
static_assert(ANORITH == 347);
static_assert(ARMALDO == 348);
static_assert(FEEBAS == 349);
static_assert(MILOTIC == 350);
static_assert(CASTFORM == 351);
static_assert(KECLEON == 352);
static_assert(SHUPPET == 353);
static_assert(BANETTE == 354);
static_assert(DUSKULL == 355);
static_assert(DUSCLOPS == 356);
static_assert(TROPIUS == 357);
static_assert(CHIMECHO == 358);
static_assert(ABSOL == 359);
static_assert(WYNAUT == 360);
static_assert(SNORUNT == 361);
static_assert(GLALIE == 362);
static_assert(SPHEAL == 363);
static_assert(SEALEO == 364);
static_assert(WALREIN == 365);
static_assert(CLAMPERL == 366);
static_assert(HUNTAIL == 367);
static_assert(GOREBYSS == 368);
static_assert(RELICANTH == 369);
static_assert(LUVDISC == 370);
static_assert(BAGON == 371);
static_assert(SHELGON == 372);
static_assert(SALAMENCE == 373);
static_assert(BELDUM == 374);
static_assert(METANG == 375);
static_assert(METAGROSS == 376);
static_assert(REGIROCK == 377);
static_assert(REGICE == 378);
static_assert(REGISTEEL == 379);
static_assert(LATIAS == 380);
static_assert(LATIOS == 381);
static_assert(KYOGRE == 382);
static_assert(GROUDON == 383);
static_assert(RAYQUAZA == 384);
static_assert(JIRACHI == 385);
static_assert(DEOXYS == 386);
static_assert(TURTWIG == 387);
static_assert(GROTLE == 388);
static_assert(TORTERRA == 389);
static_assert(CHIMCHAR == 390);
static_assert(MONFERNO == 391);
static_assert(INFERNAPE == 392);
static_assert(PIPLUP == 393);
static_assert(PRINPLUP == 394);
static_assert(EMPOLEON == 395);
static_assert(STARLY == 396);
static_assert(STARAVIA == 397);
static_assert(STARAPTOR == 398);
static_assert(BIDOOF == 399);
static_assert(BIBAREL == 400);
static_assert(KRICKETOT == 401);
static_assert(KRICKETUNE == 402);
static_assert(SHINX == 403);
static_assert(LUXIO == 404);
static_assert(LUXRAY == 405);
static_assert(BUDEW == 406);
static_assert(ROSERADE == 407);
static_assert(CRANIDOS == 408);
static_assert(RAMPARDOS == 409);
static_assert(SHIELDON == 410);
static_assert(BASTIODON == 411);
static_assert(BURMY == 412);
static_assert(WORMADAM == 413);
static_assert(MOTHIM == 414);
static_assert(COMBEE == 415);
static_assert(VESPIQUEN == 416);
static_assert(PACHIRISU == 417);
static_assert(BUIZEL == 418);
static_assert(FLOATZEL == 419);
static_assert(CHERUBI == 420);
static_assert(CHERRIM == 421);
static_assert(SHELLOS == 422);
static_assert(GASTRODON == 423);
static_assert(AMBIPOM == 424);
static_assert(DRIFLOON == 425);
static_assert(DRIFBLIM == 426);
static_assert(BUNEARY == 427);
static_assert(LOPUNNY == 428);
static_assert(MISMAGIUS == 429);
static_assert(HONCHKROW == 430);
static_assert(GLAMEOW == 431);
static_assert(PURUGLY == 432);
static_assert(CHINGLING == 433);
static_assert(STUNKY == 434);
static_assert(SKUNTANK == 435);
static_assert(BRONZOR == 436);
static_assert(BRONZONG == 437);
static_assert(BONSLY == 438);
static_assert(MIME_JR == 439);
static_assert(HAPPINY == 440);
static_assert(CHATOT == 441);
static_assert(SPIRITOMB == 442);
static_assert(GIBLE == 443);
static_assert(GABITE == 444);
static_assert(GARCHOMP == 445);
static_assert(MUNCHLAX == 446);
static_assert(RIOLU == 447);
static_assert(LUCARIO == 448);
static_assert(HIPPOPOTAS == 449);
static_assert(HIPPOWDON == 450);
static_assert(SKORUPI == 451);
static_assert(DRAPION == 452);
static_assert(CROAGUNK == 453);
static_assert(TOXICROAK == 454);
static_assert(CARNIVINE == 455);
static_assert(FINNEON == 456);
static_assert(LUMINEON == 457);
static_assert(MANTYKE == 458);
static_assert(SNOVER == 459);
static_assert(ABOMASNOW == 460);
static_assert(WEAVILE == 461);
static_assert(MAGNEZONE == 462);
static_assert(LICKILICKY == 463);
static_assert(RHYPERIOR == 464);
static_assert(TANGROWTH == 465);
static_assert(ELECTIVIRE == 466);
static_assert(MAGMORTAR == 467);
static_assert(TOGEKISS == 468);
static_assert(YANMEGA == 469);
static_assert(LEAFEON == 470);
static_assert(GLACEON == 471);
static_assert(GLISCOR == 472);
static_assert(MAMOSWINE == 473);
static_assert(PORYGON_Z == 474);
static_assert(GALLADE == 475);
static_assert(PROBOPASS == 476);
static_assert(DUSKNOIR == 477);
static_assert(FROSLASS == 478);
static_assert(ROTOM == 479);
static_assert(UXIE == 480);
static_assert(MESPRIT == 481);
static_assert(AZELF == 482);
static_assert(DIALGA == 483);
static_assert(PALKIA == 484);
static_assert(HEATRAN == 485);
static_assert(REGIGIGAS == 486);
static_assert(GIRATINA == 487);
static_assert(CRESSELIA == 488);
static_assert(PHIONE == 489);
static_assert(MANAPHY == 490);
static_assert(DARKRAI == 491);
static_assert(SHAYMIN == 492);
static_assert(ARCEUS == 493);
static_assert(EGG == 494);
static_assert(BAD_EGG == 495);
static_assert(NIDORAN == 496);
static_assert(NORMAL == 0);
static_assert(FIGHTING == 1);
static_assert(FLYING == 2);
static_assert(POISON == 3);
static_assert(GROUND == 4);
static_assert(ROCK == 5);
static_assert(BUG == 6);
static_assert(GHOST == 7);
static_assert(STEEL == 8);
static_assert(UNKNOWN == 9);
static_assert(FIRE == 10);
static_assert(WATER == 11);
static_assert(GRASS == 12);
static_assert(ELECTRIC == 13);
static_assert(PSYCHIC == 14);
static_assert(ICE == 15);
static_assert(DRAGON == 16);
static_assert(DARK == 17);
