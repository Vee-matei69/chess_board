Electronic chess board


# get the initial board layout - which squares the pieces are on - 
when initializing, each piece is given a xpos and ypos

# if a piece is lifted, scan the board -
-get the new layout of the board - empty squares and occupied squares[current_matrix] - get the row-col (lifted_square)
-go through each board piece and find the one that has xpos and ypos same as the (lifted_square)
-check for possible moves - (check for possible squares) - feed them into an array
-compare the [possible_squares] and [current_matrix] - 
-if 

possible_squares, available_squares, valid_squares