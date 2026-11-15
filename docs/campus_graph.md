# Campus Graph

Source: the campus signboard map. The lawns are left out because nobody routes to a lawn.
Distances are ESTIMATED from the map using the campus area of about 6 acres. They are not measured.

## Locations
| ID | Location |
|---|---|
| 1 | Main Gate |
| 2 | Gate 2 |
| 3 | Gate 3 |
| 4 | Gate 4 |
| 5 | Parking Area |
| 6 | Academic Block 1 |
| 7 | Academic Block 2 (EE building) |
| 8 | Academic Block 3 |
| 9 | Library and Cafe (multi-purpose building) |
| 10 | Mosque |
| 11 | Sports Room Gymnasium |
| 12 | Futsal Ground |
| 13 | Badminton Court |
| 14 | Basketball Court (also basketball, throwball and volleyball) |

## Connections (estimated metres)
Main Gate-Parking Area 90, Gate 2-Parking Area 30, Main Gate-Academic Block 1 70, Main Gate-Academic Block 2 55,
Main Gate-Basketball Court 45, Gate 2-Basketball Court 25, Gate 2-Library and Cafe 75, Gate 3-Library and Cafe 30,
Gate 3-Academic Block 1 45, Gate 3-Mosque 75, Gate 4-Mosque 15, Gate 4-Academic Block 3 50,
Mosque-Academic Block 1 40, Academic Block 1-Academic Block 3 40, Academic Block 1-Academic Block 2 45,
Academic Block 2-Academic Block 3 25, Basketball Court-Academic Block 1 40, Library and Cafe-Futsal Ground 20,
Library and Cafe-Sports Room Gymnasium 35, Sports Room Gymnasium-Futsal Ground 30, Futsal Ground-Badminton Court 35,
Library and Cafe-Academic Block 1 25.

## Food places
| ID | Name | Location |
|---|---|---|
| 1 | Main Cafeteria | Library and Cafe |
| 2 | Badr Canteen | Mosque |
| 3 | Tasty Canteen | Academic Block 2 |
| 4 | Juice Center | Academic Block 3 |

## Route algorithm
BFS finds the route with the fewest connections, not the shortest distance. Example: from Gate 2 to Mosque it returns
Gate 2, Library and Cafe, Gate 3, Mosque (3 connections, 180 m), although Gate 2, Library and Cafe, Academic Block 1, Mosque
has the same number of connections and is shorter (140 m). A weighted algorithm such as Dijkstra would be needed to always get the shortest distance.
