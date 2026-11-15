# Function Contracts

| Function | Purpose | Parameters | Returns | Owner |
|---|---|---|---|---|
| loadLocations | Read locations.csv | path | number of locations loaded, or -1 if the file cannot be opened | Person 1 |
| loadRoutes | Read routes.csv | path | number of routes loaded, or -1 | Person 1 |
| findLocation | Find a location by exact name (ignores case) | name | location ID, or -1 if not found | Person 1 |
| searchLocations | Find locations whose name contains the text | query, ids array, maximum | number of matches | Person 1 |
| getLocationName | Name of a location | id | the name, or NULL if the ID is invalid | Person 1 |
| getDistance | Distance of a direct road between two locations | from, to | distance in metres, or 0 if there is no direct road | Person 1 |
| findRoute | BFS shortest route by number of connections | start, end, path array, path length, total distance | 1 found, 0 no route, -1 invalid location | Person 1 |
| printRoute | Print a route as numbered steps with distance | start, end | nothing | Person 1 |
| normalizeQuery | Lowercase a query and remove punctuation and extra spaces | text (changed in place) | nothing | Person 1 |
| detectIntent | Decide what the user is asking | normalized query | an INTENT_ constant | Person 1 |
| processQuery | Normalize, detect the intent and call the right module | input text | nothing | Person 1 |
| loadFood | Read food.csv | path | number of items loaded, or -1 | Person 2 |
| displayFood | Print every food item in a table | none | nothing | Person 2 |
| searchFood | Search food by name or category (partial, ignores case) | query | number of matches printed | Person 2 |
| searchByBudget | Items with price at most the budget, optionally for one category | maxPrice, category (empty for all) | number of matches printed | Person 2 |
| showMenuByVendor | Print the menu of one cafeteria | vendorId | number of items printed | Person 2 |
| compareMenus | Compare the prices of up to three cafeterias, showing - for items not sold | vendorIds, count | number of item rows printed | Person 2 |
| loadCafeterias | Read cafeterias.csv | path | number loaded, or -1 | Person 2 |
| listCafeterias | Print all cafeterias with location and hours | none | nothing | Person 2 |
| viewCafeteria | Print one cafeteria, its location, hours and menu | id | 1 if found, 0 if not | Person 2 |
| loadFavorites | Read favorites.txt (a missing file means no favorites yet) | path | number loaded | Person 2 |
| addFavorite | Add an item and save the file | type, id | 1 added, 0 already there, -1 ID does not exist, -2 list full | Person 2 |
| removeFavorite | Remove an item and save the file | type, id | 1 removed, 0 not in favorites | Person 2 |
| listFavorites | Print all favorites with names | none | nothing | Person 2 |
| showMainMenu | Print the main menu | none | nothing | Person 3 |
| readChoice | Read a menu number safely | none | the number, -1 if not a number, 0 if input ended | Person 3 |
| printMessage | Print one line of text | text | nothing | Person 3 |
