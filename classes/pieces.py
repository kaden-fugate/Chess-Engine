# piece will have a color as well as an array of valid moves. 
# we will have child classes for specific types of pieces such
# as king or pawn.
class Piece:
    
    def __init__(self, pos_x, pos_y, color):
        self.color = color
        self.valid_moves = []
        self.pos_x = pos_x
        self.pos_y = pos_y
    
    def getColor(self):
        return self.color
    
    def getValidMoves(self):
        return self.valid_moves

    def getIcon():
        pass

    def setValidMoves():
        pass

# King class
class King(Piece):

    # initialize king class
    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265A' if color == 'white' else '\u2654'
        self.directions = [(-1,1), (0,1), (1,1),
                           (-1,0),        (1,0),
                           (-1,-1),(0,-1),(1,-1)]

    # kings icon
    def getIcon(self): return self.icon
                
    def isCheck(self):
        return False

    def setValidMoves(self, board):
        
        for dx, dy in self.directions:

            # check is within the board
            if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                board_pos = board[self.pos_y + dy][self.pos_x + dx]
                
                # check move does not put king in check
                if not board_pos or (board_pos and board_pos.getColor() != self.color):
                    self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))

class Queen(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265B' if color == 'white' else '\u2655'
        self.directions = [[(-1,1),(-2,2),(-3,3),(-4,4),(-5,5),(-6,6),(-7,7)],
                           [(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7)],
                           [(-1,-1),(-2,-2),(-3,-3),(-4,-4),(-5,-5),(-6,-6),(-7,-7)],
                           [(1,-1),(2,-2),(3,-3),(4,-4),(5,-5),(6,-6),(7,-7)],
                           [(0,1),(0,2),(0,3),(0,4),(0,5),(0,6),(0,7)], 
                           [(-1,0),(-2,0),(-3,0),(-4,0),(-5,0),(-6,0),(-7,0)],       
                           [(1,0),(2,0),(3,0),(4,0),(5,0),(6,0),(7,0)],
                           [(0,-1),(0,-2),(0,-3),(0,-4),(0,-5),(0,-6),(0,-7)]]

    def getIcon(self): return self.icon

    def setValidMoves(self, board):
        for direction in self.directions:

            for dx, dy in direction:

                # check is within the board
                if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                    board_pos = board[self.pos_y + dy][self.pos_x + dx]
                    
                    # check move does not put king in check
                    if not board_pos or (board_pos and board_pos.getColor() != self.color):
                        self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))
                    else: break

class Rook(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265C' if color == 'white' else '\u2656'
        self.directions = [ [(0,1),(0,2),(0,3),(0,4),(0,5),(0,6),(0,7)], 
                            [(-1,0),(-2,0),(-3,0),(-4,0),(-5,0),(-6,0),(-7,0)],       
                            [(1,0),(2,0),(3,0),(4,0),(5,0),(6,0),(7,0)],
                            [(0,-1),(0,-2),(0,-3),(0,-4),(0,-5),(0,-6),(0,-7)]
                            ]

    def getIcon(self): return self.icon

    def setValidMoves(self, board):
        for direction in self.directions:

            for dx, dy in direction:

                # check is within the board
                if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                    board_pos = board[self.pos_y + dy][self.pos_x + dx]
                    
                    # check move does not put king in check
                    if not board_pos or (board_pos and board_pos.getColor() != self.color):
                        self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))
                    else: break

class Bishop(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265D' if color == 'white' else '\u2657'
        self.directions = [[(-1,1),(-2,2),(-3,3),(-4,4),(-5,5),(-6,6),(-7,7)],
                           [(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7)],
                           [(-1,-1),(-2,-2),(-3,-3),(-4,-4),(-5,-5),(-6,-6),(-7,-7)],
                           [(1,-1),(2,-2),(3,-3),(4,-4),(5,-5),(6,-6),(7,-7)]]

    def getIcon(self): return self.icon

    def setValidMoves(self, board):
        for direction in self.directions:

            for dx, dy in direction:

                # check is within the board
                if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                    board_pos = board[self.pos_y + dy][self.pos_x + dx]
                    
                    # check move does not put king in check
                    if not board_pos or (board_pos and board_pos.getColor() != self.color):
                        self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))
                    else: break

class Knight(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265E' if color == 'white' else '\u2658'
        self.directions = [      (-1,2),  (1,2),
                           (-2,1),              (2,1),
                           (-2,-1),             (2,-1),
                                 (-1,-2),  (1,-2)]

    def getIcon(self): return self.icon

    def setValidMoves(self, board):
        
        for dx, dy in self.directions:

            # check is within the board
            if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                board_pos = board[self.pos_y + dy][self.pos_x + dx]
                
                # check move does not put king in check
                if not board_pos or (board_pos and board_pos.getColor() != self.color):
                    self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))

class Pawn(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265F' if color == 'white' else '\u2659'
        self.directions = [(0,-2),(-1,-1),(0,-1),(1,-1)] if color == 'black' else [(0,2),(-1,1),(0,1),(1,1)]
        self.initial_jump = True # pas can initially jump 2 squares before moving

    def getIcon(self): return self.icon

    def setValidMoves(self, board):

        for idx, direction in enumerate(self.directions):

                dx, dy = direction
                new_x, new_y = self.pos_x + dx, self.pos_y + dy
                print(f"===================================\n- idx: {idx}\n- coords: ({new_x},{new_y})\n- original: ({self.pos_x},{self.pos_y})\n- direction: {direction}\n===================================")

                if 0 <= new_x < 8 and 0 <= new_y < 8:

                    board_pos = board[new_y][new_x]
                    prev_pos = board[new_y-1][new_x] if self.color == 'black' else board[new_y+1][new_x]

                    # if idx 0 (2 square jump), and initial jump variable is true 
                    # and the two square required in jump are not blocked (board_pos 
                    # and prev_pos), 2 square jump is valid move

                    if idx == 0 and self.initial_jump and (not board_pos and not prev_pos):
                        print(f"({new_x},{new_y}): APPENDING PAWN JUMPS 2!")
                        self.valid_moves.append( (new_x, new_y) )

                    # if idx 1 or 3 (pawn takes), and the board has a piece that 
                    # is not the color of the pawn, pawn takes is a valid move. 
                    elif (idx == 1 or idx == 3) and (board_pos and board_pos.getColor() != self.color): 
                        print(f"({new_x},{new_y}): APPENDING PAWN TAKES!")
                        self.valid_moves.append( (new_x, new_y) )
                    
                    # if idx 2 (pawn takes step forward) and the spot in front of
                    # the pawn is not blocked, step forward is valid move
                    elif idx == 2 and not board_pos:
                        print(f"({new_x},{new_y}): APPENDING PAWN TAKES STEP!")
                        self.valid_moves.append( (new_x, new_y) )