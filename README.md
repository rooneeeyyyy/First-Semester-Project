# FAST Navigator & Cafeteria Hub

A C console program for the FAST campus. It searches food and prices, lists the campus canteens and their menus,
finds routes between campus locations, and has a small rule-based assistant for English and Roman Urdu questions.

## Features
- Food search by name or category, and a maximum-budget filter
- Cafeteria directory with location, opening hours, menu, and a price comparison of up to three cafeterias
- Campus locations and BFS route finding (fewest connections) with an estimated distance
- Rule-based assistant (a small command interpreter, not a general AI model)
- Favorites that are saved to a file and kept after the program is closed

## Build and run
Open a terminal in the project root folder and run (all on one line):

    gcc -Wall -Wextra -Iinclude src/main.c src/ui.c src/map.c src/food.c src/cafeteria.c src/utils.c src/route.c src/assistant.c src/favorites.c -o fast_navigator

Then start it from the same folder, because the data files are found by relative path:

    .\fast_navigator.exe

## Project structure
- src/ - source files (main.c, ui.c, map.c, route.c, food.c, cafeteria.c, favorites.c, assistant.c, utils.c)
- include/ - header files
- data/ - locations.csv, routes.csv, food.csv, cafeterias.csv, and favorites.txt (created by the program)
- docs/ - technical map, function contracts, data fields, campus graph, data sources, test sheet, user journey

## Assistant examples
- English: `biryani price`, `food under 150`, `cheap food`, `show cafeterias`, `badr canteen menu`, `where is the library`, `route from Main Gate to Mosque`
- Roman Urdu: `biryani kahan milegi`, `sasta khana`, `biryani kitne ka hai`, `mosque qareeb kya hai`, `main gate se library tak`
- Type `help` in the assistant to see the examples. Other phrases get a fallback message.

## Data status and limitations
- Locations, connections and food places come from the campus signboard map. Distances are estimated, not measured.
- Opening hours (08:00-16:00 for all canteens) were provided by the project member.
- The menu items and prices in data/food.csv are sample items until the real menus are added.
- Routes use fewest connections (BFS), so the shortest distance is not always chosen.
- The assistant understands only a small documented set of phrases.
- CSV fields must not contain commas.
- See docs/data_sources.md for the source and date of each kind of data.

## Team
- Person 1: Core and Algorithms (map, route, assistant)
- Person 2: Data and Backend (food, cafeterias, CSV files, favorites)
- Person 3: Interface and Delivery (menus, validation, documentation, demo)
