import json
import re

from collections import defaultdict as dd

TRAINER_DATA_FILE_NAME = 'src/data/trainers.h'
TRAINER_MONS_FILE_NAME = 'src/data/trainer_parties.h'
ITEM_DATA_FILE_NAME = 'src/data/items.h'
MOVE_NAME_FILE_NAME = 'src/data/text/move_names.h'
MONS_NAME_FILE_NAME = 'src/data/text/species_names.h'
CLSS_NAME_FILE_NAME = 'src/data/text/trainer_class_names.h'
ABILITY_DATA_FILE_NAME = 'src/data/text/abilities.h'
BASE_STATS_DATA_FILE_NAME = 'src/data/pokemon/base_stats.h'

TRAINER_MONS_DEFN_LEAD = re.compile(r'static const struct (TrainerMon\w+) (sParty_(\w+))\[\] = \{')
TRAINER_DATA_DEFN_LEAD = re.compile(r'\[TRAINER_(\w+)\] =')

ITEM_NAMES = {}
MOVE_NAMES = {}
SPECIES_NAMES = {}
TRCLASS_NAMES = {}
ABILITY_NAMES = {}
SPECIES_ABILITIES = {}
MEGA_STONES = [
    'ITEM_VENUSAURITE',
    'ITEM_CHARIZARDITE_X',
    'ITEM_CHARIZARDITE_Y',
    'ITEM_BLASTOISINITE',
    'ITEM_BEEDRILLITE',
    'ITEM_PIDGEOTITE',
    'ITEM_ALAKAZITE',
    'ITEM_SLOWBRONITE',
    'ITEM_GENGARITE',
    'ITEM_KANGASKHANITE',
    'ITEM_PINSIRITE',
    'ITEM_GYARADOSITE',
    'ITEM_AERODACTYLITE',
    'ITEM_MEWTWONITE_X',
    'ITEM_MEWTWONITE_Y',
    'ITEM_AMPHAROSITE',
    'ITEM_STEELIXITE',
    'ITEM_SCIZORITE',
    'ITEM_HERACRONITE',
    'ITEM_HOUNDOOMINITE',
    'ITEM_TYRANITARITE',
    'ITEM_SCEPTILITE',
    'ITEM_BLAZIKENITE',
    'ITEM_SWAMPERTITE',
    'ITEM_GARDEVOIRITE',
    'ITEM_SABLENITE',
    'ITEM_MAWILITE',
    'ITEM_AGGRONITE',
    'ITEM_MEDICHAMITE',
    'ITEM_MANECTITE',
    'ITEM_SHARPEDONITE',
    'ITEM_CAMERUPTITE',
    'ITEM_ALTARIANITE',
    'ITEM_BANETTITE',
    'ITEM_ABSOLITE',
    'ITEM_GLALITITE',
    'ITEM_SALAMENCITE',
    'ITEM_METAGROSSITE',
    'ITEM_LATIASITE',
    'ITEM_LATIOSITE',
    'ITEM_LOPUNNITE',
    'ITEM_GARCHOMPITE',
    'ITEM_LUCARIONITE',
    'ITEM_ABOMASITE',
    'ITEM_GALLADITE',
    'ITEM_AUDINITE',
    'ITEM_DIANCITE',
    'ITEM_ULTRANECROZIUM_Z',
]

ITEM_NAMES_OVERRIDES = {
    'ITEM_HEAVY_DUTY_BOOTS': 'Heavy-Duty Boots',
    'ITEM_NEVER_MELT_ICE': 'Never-Melt Ice',
    'ITEM_SAFETY_GOGGLES': 'Safety Goggles',
    'ITEM_WEAKNESS_POLICY': 'Weakness Policy',
}

MOVE_NAMES_OVERRIDES = {
    'MOVE_ANCIENT_POWER': 'Ancient Power',
    'MOVE_BANEFUL_BUNKER': 'Baneful Bunker',
    'MOVE_BURNING_JEALOUSY': 'Burning Jealousy',
    'MOVE_CLANGOROUS_SOUL': 'Clangorous Soul',
    'MOVE_DARKEST_LARIAT': 'Darkest Lariat',
    'MOVE_DAZZLING_GLEAM': 'Dazzling Gleam',
    'MOVE_DIAMOND_STORM': 'Diamond Storm',
    'MOVE_DOUBLE_IRON_BASH': 'Double Iron Bash',
    'MOVE_DRAGON_BREATH': 'Dragon Breath',
    'MOVE_DRAGON_HAMMER': 'Dragon Hammer',
    'MOVE_DRAINING_KISS': 'Draining Kiss',
    'MOVE_DUAL_WINGBEAT': 'Dual Wingbeat',
    'MOVE_DYNAMAX_CANNON': 'Dynamax Cannon',
    'MOVE_ELECTRIC_TERRAIN': 'Electric Terrain',
    'MOVE_EXTREME_SPEED': 'Extreme Speed',
    'MOVE_FALSE_SURRENDER': 'False Surrender',
    'MOVE_FEATHER_DANCE': 'Feather Dance',
    'MOVE_FIRST_IMPRESSION': 'First Impression',
    'MOVE_FISHIOUS_REND': 'Fishious Rend',
    'MOVE_FLORAL_HEALING': 'Floral Healing',
    'MOVE_FREEZING_GLARE': 'Freezing Glare',
    'MOVE_GLACIAL_LANCE': 'Glacial Lance',
    'MOVE_HEADLONG_RUSH': 'Headlong Rush',
    'MOVE_HIGH_HORSEPOWER': 'High Horsepower',
    'MOVE_HIGH_JUMP_KICK': 'High Jump Kick',
    'MOVE_HYPERSPACE_HOLE': 'Hyperspace Hole',
    'MOVE_MYSTICAL_FIRE': 'Mystical Fire',
    'MOVE_OBLIVION_WING': 'Oblivion Wing',
    'MOVE_PHANTOM_FORCE': 'Phantom Force',
    'MOVE_PHOTON_GEYSER': 'Photon Geyser',
    'MOVE_POWER_UP_PUNCH': 'Power-Up Punch',
    'MOVE_PRECIPICE_BLADES': 'Precipice Blades',
    'MOVE_PSYCHIC_FANGS': 'Psychic Fangs',
    'MOVE_REVELATION_DANCE': 'Revelation Dance',
    'MOVE_SHELL_SIDE_ARM': 'Shell Side Arm',
    'MOVE_SPECTRAL_THIEF': 'Spectral Thief',
    'MOVE_SPIRIT_SHACKLE': 'Spirit Shackle',
    'MOVE_STEAM_ERUPTION': 'Steam Eruption',
    'MOVE_STOMPING_TANTRUM': 'Stomping Tantrum',
    'MOVE_STRANGE_STEAM': 'Strange Steam',
    'MOVE_THUNDEROUS_KICK': 'Thunderous Kick',
    'MOVE_THUNDER_PUNCH': 'Thunder Punch',   
}

MONS_NAMES_OVERRIDES = {
    'SPECIES_ARTICUNO_GALARIAN': 'Articuno-Galar',
    'SPECIES_BARRASKEWDA': 'Barraskewda',
    'SPECIES_BLACEPHALON': 'Blacephalon',
    'SPECIES_CALYREX_ICE_RIDER': 'Calyrex-Ice',
    'SPECIES_CENTISKORCH': 'Centiskorch',
    'SPECIES_CORSOLA_GALARIAN': 'Corsola-Galar',
    'SPECIES_CORVIKNIGHT': 'Corviknight',
    'SPECIES_CORVISQUIRE': 'Corvisquire',
    'SPECIES_CRABOMINABLE': 'Crabominable',
    'SPECIES_DUGTRIO_ALOLAN': 'Dugtrio-Alola',
    'SPECIES_EXEGGUTOR_ALOLAN': 'Exeggutor-Alola',
    'SPECIES_FARFETCHD_GALARIAN': 'Farfetch\'d-Galar',
    'SPECIES_GEODUDE_ALOLAN': 'Geodude-Alola',
    'SPECIES_GOLEM_ALOLAN': 'Golem-Alola',
    'SPECIES_INDEEDEE_FEMALE': 'Indeedee-F',
    'SPECIES_KYUREM_BLACK': 'Kyurem-Black',
    'SPECIES_LYCANROC_DUSK': 'Lycanroc-Dusk',
    'SPECIES_LYCANROC_MIDNIGHT': 'Lycanroc-Midnight',
    'SPECIES_MAROWAK_ALOLAN': 'Marowak-Alola',
    'SPECIES_MEOWSTIC_FEMALE': 'Meowstic-F',
    'SPECIES_MOLTRES_GALARIAN': 'Moltres-Galar',
    'SPECIES_NINETALES_ALOLAN': 'Ninetales-Alola',
    'SPECIES_ORICORIO_POM_POM': 'Oricorio-Pom-Pom',
    'SPECIES_POLTEAGEIST': 'Polteagiest',
    'SPECIES_RAICHU_ALOLAN': 'Raichu-Alola',
    'SPECIES_RAPIDASH_GALARIAN': 'Rapidash-Galar',
    'SPECIES_ROTOM_FAN': 'Rotom-Fan',
    'SPECIES_ROTOM_MOW': 'Rotom-Mow',
    'SPECIES_ROTOM_WASH': 'Rotom-Wash',
    'SPECIES_SANDSLASH_ALOLAN': 'Sandslash-Alola',
    'SPECIES_SLOWBRO_GALARIAN': 'Slowbro-Galar',
    'SPECIES_SLOWKING_GALARIAN': 'Slowking-Galar',
    'SPECIES_STUNFISK_GALARIAN': 'Stunfisk-Galar',
    'SPECIES_TOXTRICITY_LOW_KEY': 'Toxtricity-Low-Key',
    'SPECIES_WEEZING_GALARIAN': 'Weezing-Galar',
    'SPECIES_ZAPDOS_GALARIAN': 'Zapdos-Galar',
}

REMATCH_BOSSES = set([
    'Roxanne',
    'Brawly'
])

IGNORED_BOSSES = set([
    'ROXANNE_3',
    'ROXANNE_4',
    'ROXANNE_5',
    'BRAWLY_3',
    'BRAWLY_4',
    'BRAWLY_5',
    'WATTSON_2',
    'WATTSON_3',
    'WATTSON_4',
    'WATTSON_5',
    'FLANNERY_2',
    'FLANNERY_3',
    'FLANNERY_4',
    'FLANNERY_5',
    'NORMAN_2',
    'NORMAN_3',
    'NORMAN_4',
    'NORMAN_5',
    'WINONA_2',
    'WINONA_3',
    'WINONA_4',
    'WINONA_5',
    'TATE_AND_LIZA_2',
    'TATE_AND_LIZA_3',
    'TATE_AND_LIZA_4',
    'TATE_AND_LIZA_5',
    'JUAN_2',
    'JUAN_3',
    'JUAN_4',
    'JUAN_5',
])

BOSSES_NO_EXTRA_DATA = set([
    'Wattson',
    'Flannery',
    'Norman',
    'Winona',
    'Tate & Liza',
    'Juan',
    'Jasmine',
    'Lucy',
    'Tucker',
    'Anabel',
    'Noland',
])

LEVEL_SCALED_BOSSES = {
    'MORTY': 65,
    'LEADER_JASMINE': 65,
    'GRUNT_LILYCOVECITY': 65,
    'LUCY_1': 74,
    'TUCKER_1': 74,
    'ANABEL_1': 74,
}

EXTENDED_ABILITY_NAMES = {

}

# - TrainerMonItemCustomMoves: has an item, has a custom moveset
# - TrainerMonItemDefaultMoves: has an item, moveset is based on level-up learnset
# - TrainerMonNoItemCustomMoves: has no item, has a custom moveset
# - TrainerMonNoItemDefaultMoves: has no item, moveset is based on level-up learnset

def import_item_names():
    with open(ITEM_DATA_FILE_NAME, 'r') as item_data_file:
        item_key = ''
        item_name = ''
        for line in item_data_file:
            l = line.strip()
            if re.match(r'\[\w+\] =', l):
                item_key = l[1:-3]
            elif l.startswith('.name'):
                item_name = l.split('=')[1].strip()[3:-3]
                if item_key in ITEM_NAMES_OVERRIDES:
                    item_name = ITEM_NAMES_OVERRIDES[item_key]
                ITEM_NAMES[item_key] = item_name


def _import_simple_name_mapping(data_file_name, target_dict, prefix, overrides={}):
    with open(data_file_name, 'r') as data_file:
        key = ''
        name = ''
        r = re.compile(f'\[({prefix}_(\w+))\] = _\("(.+)"\),')
        for line in data_file:
            if r.match(line.strip()):
                (key, _, name) = r.match(line.strip()).groups()
                if key in overrides:
                    name = overrides[key]
                target_dict[key] = name


def import_move_names():
    _import_simple_name_mapping(MOVE_NAME_FILE_NAME, MOVE_NAMES, 'MOVE', MOVE_NAMES_OVERRIDES)


def import_species_names():
    _import_simple_name_mapping(MONS_NAME_FILE_NAME, SPECIES_NAMES, 'SPECIES', MONS_NAMES_OVERRIDES)


def import_trainer_class_names():
    _import_simple_name_mapping(CLSS_NAME_FILE_NAME, TRCLASS_NAMES, 'TRAINER_CLASS')


def import_ability_names():
    with open(ABILITY_DATA_FILE_NAME, 'r') as ability_data_file:
        for line in ability_data_file:
            # seek through the file until finding the start of the ability names
            if line.strip() == '#if B_EXPANDED_ABILITY_NAMES == TRUE':
                break
        
        key = ''
        name = ''
        r = re.compile(r'\[(ABILITY_(\w+))\] = _\("(.+)"\),')
        next(ability_data_file)
        for line in ability_data_file:
            if line.strip().startswith('#else'):
                break

            if r.match(line.strip()):
                (key, _, name) = r.match(line.strip()).groups()
                if key == 'ABILITY_WRESTLERS_MARK':
                    ABILITY_NAMES[key] = 'Wrestler\'s Mark'
                else:
                    ABILITY_NAMES[key] = name


def import_pokemon_abilities():
    with open(BASE_STATS_DATA_FILE_NAME, 'r') as base_stats_data_file:
        for line in base_stats_data_file:
            if line.strip() == 'const struct BaseStats gBaseStats[] =':
                break
        
        key = ''
        abilities = []
        r = re.compile(r'\[(SPECIES_(\w+))\] =')
        for line in base_stats_data_file:
            l = line.strip()
            if r.match(l):
                (key, _) = r.match(l).groups()
            elif l.startswith('.abilities'):
                abilities = [s.strip() for s in l.split('=')[1].strip()[1:-2].strip().split(',')]
                if key not in SPECIES_ABILITIES:        # only import once; dodge the battle engine preproc flag
                    SPECIES_ABILITIES[key] = abilities


def parse_boss_parties():
    boss_parties = {}
    with open(TRAINER_MONS_FILE_NAME, 'r') as trainer_mons_file:
        party = []
        mon = {}
        trkey = ''
        tritems = False
        trmoves = False

        for line in trainer_mons_file:
            l = line.strip()
            if l == '':         # empty, skip
                continue
            elif l[0] == '{':   # new mon
                mon = {}
            elif l == '};':     # done with a party
                # check if this is a boss (i.e. if their mons define an ability)
                if 'abilityNums' in party[0]:
                    boss_parties[trkey] = {}
                    boss_parties[trkey]['items'] = tritems
                    boss_parties[trkey]['moves'] = trmoves
                    boss_parties[trkey]['party'] = party
                # otherwise just skip, this is a non-boss trainer
                # reset some stuff though
                tritems = False
                trmoves = False
                party = []
            elif l[0] == '}':   # done with a mon
                party.append(mon)
            elif TRAINER_MONS_DEFN_LEAD.match(l):
                (typedef, trkey, _) = TRAINER_MONS_DEFN_LEAD.match(l).groups()
                if typedef == 'TrainerMonItemCustomMoves':
                    tritems = True
                    trmoves = True
                elif typedef == 'TrainerMonItemDefaultMoves':
                    tritems = True
                elif typedef == 'TrainerMonNoItemCustomMoves':
                    trmoves = True
            else:
                pieces = [s.strip() for s in l.split('=')]
                if pieces[1][-1] == ',':
                    pieces[1] = pieces[1][0:-1]

                if pieces[1][0] == '{':
                    pieces[1] = [s.strip() for s in pieces[1][1:-1].split(',')]
                elif pieces[1].isdigit():
                    pieces[1] = int(pieces[1])

                mon[pieces[0][1:]] = pieces[1]
    return boss_parties


def parse_bosses(boss_parties):
    bosses = {}
    with open(TRAINER_DATA_FILE_NAME, 'r') as trainer_data_file:
        next(trainer_data_file) # skip the first line

        tr_class = ''
        tr_name = ''
        tr_party_id = ''
        tr_key = ''

        for line in trainer_data_file:
            l = line.strip()
            if l == '':                         # empty line
                continue
            elif l[0] == '{' or l == '};':      # new data def or end of file
                continue
            elif l[0] == '}':                   # end of trainer
                if tr_party_id in boss_parties: # check if this is a boss
                    bosses[tr_key] = {}
                    bosses[tr_key]['class'] = tr_class
                    bosses[tr_key]['name'] = tr_name
                    bosses[tr_key]['party'] = boss_parties[tr_party_id]
                
                # prep for the next one
                tr_class = ''
                tr_name = ''
                tr_party_id = ''
                tr_key = ''
            elif TRAINER_DATA_DEFN_LEAD.match(l):
                tr_key = TRAINER_DATA_DEFN_LEAD.match(l).group(1)
            elif l.startswith('.trainerClass'):
                tr_class = l.split('=')[1].strip()[0:-1]
            elif l.startswith('.party '):
                tr_party_id = l.split('=')[2].strip()[0:-2]
            elif l.startswith('.trainerName'):
                tr_name = l.split('=')[1].strip()[3:-3]
    return bosses


def to_showdown_json_sets(bosses):
    sets = {}
    for boss_key in bosses:
        if boss_key in IGNORED_BOSSES:
            continue

        # the boss key might contain some important info about trainers with the same class + name
        # e.g. assorted grunt mini-bosses being marked as their locations
        boss_data = bosses[boss_key]
        boss_class = TRCLASS_NAMES[boss_data['class']].replace('{PKMN}', u'Pokémon')
        boss_name = boss_data['name']
        boss_extra = None
        if '_' in boss_key:
            boss_extra = ' '.join(boss_key.split('_')[1:]).title()

        boss_items = boss_data['party']['items']
        boss_party = boss_data['party']['party']
        for boss_mon in boss_party:
            species = SPECIES_NAMES[boss_mon['species']]
            item = None if not boss_items or 'heldItem' not in boss_mon or boss_mon['heldItem'] == 'ITEM_NONE' else ITEM_NAMES[boss_mon['heldItem']]
            moves = [MOVE_NAMES[m] for m in boss_mon['moves']]
            # nature is implicitly Hardy

            # check the level; if it's 0, get the level from level-scaling defs
            level = boss_mon['lvl']
            if int(level) == 0:
                level = LEVEL_SCALED_BOSSES.get(boss_key, -1)

            # ability needs to be sanitized: if the value is out of range, implicitly set to 0
            if len(SPECIES_ABILITIES[boss_mon['species']]) <= int(boss_mon['abilityNums']):
                ability = ABILITY_NAMES[SPECIES_ABILITIES[boss_mon['species']][0]]
            else:
                ability = ABILITY_NAMES[SPECIES_ABILITIES[boss_mon['species']][boss_mon['abilityNums']]]
            
            if boss_items and boss_mon.get('heldItem') in MEGA_STONES:
                if item == 'Necrozmaite':
                    species = species + '-Ultra'
                else:
                    species = species + '-Mega'
                    if item[-1] == 'X':
                        species = species + '-X'
                    elif item[-1] == 'Y':
                        species = species + '-Y'
            
            if species not in sets:
                sets[species] = {}
            
            sets_key = f'{boss_class} {boss_name}'
            if boss_extra is not None and boss_name not in BOSSES_NO_EXTRA_DATA:
                if boss_extra.isnumeric() and boss_name in REMATCH_BOSSES and int(boss_extra) < 3:
                    boss_extra = 'Rematch'
                elif 'Route1' in boss_extra:
                    boss_extra = boss_extra.replace('Route1', 'Route 1')
                elif 'city' in boss_extra:
                    boss_extra = boss_extra.replace('city', ' City')

                sets_key = sets_key + f' ({boss_extra})'
            
            sets[species][sets_key] = {
                'ability': ability,
                'level': level,
                'moves': moves
            }

            if item is not None:
                sets[species][sets_key]['item'] = item
    
    return sets


if __name__ == '__main__':
    import_item_names()
    import_move_names()
    import_species_names()
    import_trainer_class_names()
    import_ability_names()
    import_pokemon_abilities()

    boss_parties = parse_boss_parties()
    bosses = parse_bosses(boss_parties)

    sets = to_showdown_json_sets(bosses)

    with open('showdown_sets.json', 'w') as fp:
        fp.write(json.dumps(sets, indent=4, ensure_ascii=False))
