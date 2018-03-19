CREATE SCHEMA rps ;
CREATE TABLE game_details (game_id VARCHAR(80),
player VARCHAR(20),
rock INT,
paper INT,
scissors INT,
PRIMARY KEY(game_id, player)
);