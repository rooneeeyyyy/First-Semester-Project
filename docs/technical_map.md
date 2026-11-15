# Technical Map: FAST Navigator & Cafeteria Hub

## Modules
| Module | Files | Owner | Purpose |
|---|---|---|---|
| Interface | main.c, ui.c/.h | Person 3 | Menus, input reading, output messages |
| Food | food.c/.h | Person 2 | Load food.csv, search, budget filter, menu by vendor, compare menus |
| Cafeteria | cafeteria.c/.h | Person 2 | Load cafeterias.csv, list cafeterias, show a cafeteria and its menu |
| Favorites | favorites.c/.h | Person 2 with Person 3 | Add, remove, list and save favorites (food, cafeteria, location) |
| Map | map.c/.h | Person 1 | Load locations and routes, location lookup, distances |
| Route | route.c/.h | Person 1 | BFS route finder (fewest connections) and route printing |
| Assistant | assistant.c/.h | Person 1 | Normalize a query, detect intent, call the other modules |
| Utils | utils.c/.h | Shared | Trimming, lowercase, case-insensitive matching, CSV splitting, number parsing |

## Call flow
- main.c shows the main menu through ui and sends the user to one of the menus.
- Food menu calls food. Cafeteria menu calls cafeteria and food (menus and comparison).
- Map menu calls map and route. Favorites menu calls favorites.
- Assistant menu calls assistant. The assistant calls food, cafeteria, map and route, and never repeats their search code.
- route calls map (getDistance and the location list).
- favorites calls food, cafeteria and map to check that an ID exists.
- cafeteria calls map (location names) and food (menu by vendor).

## Data files (loaded at startup)
data/locations.csv, data/routes.csv, data/food.csv, data/cafeterias.csv, and data/favorites.txt (created by the program).
