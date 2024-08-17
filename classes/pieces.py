# piece will have a color as well as an array of valid moves. 
# we will have child classes for specific types of pieces such
# as king or pawn.
class Piece:
    
    def __init__(self, pos_x, pos_y, color):
        self.color = color
        self.valid_moves = []
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.debug_mode = False

    def getColor(self):
        return self.color
    
    def getValidMoves(self):
        return self.valid_moves
    
    def getCoords(self): return (self.pos_x, self.pos_y)
    
    def getHasMoved(self):
        pass

    def getIcon():
        pass

    def setValidMoves():
        pass

    def setCoords(self, coords):
        self.pos_x, self.pos_y = coords

    def setHasMoved(self):
        pass
    
    def setDebug(self):
        self.debug_mode = True if not self.debug_mode else False
        

# King class
class King(Piece):

    # initialize king class
    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265A' if color == 'white' else '\u2654'
        self.directions = [(-1,1), (0,1), (1,1),
                   (-2,0), (-1,0),        (1,0), (2,0),
                           (-1,-1),(0,-1),(1,-1) ]
        self.can_castle_long = False
        self.can_castle_short = False
        self.hasMoved = False

    # kings icon
    def getIcon(self): return self.icon
    def getHasMoved(self): return self.hasMoved
    def getCastleLong(self): return self.can_castle_long
    def getCastleShort(self): return self.can_castle_short
    
    def setShortCastle(self, truth_val): self.can_castle_short = truth_val
    def setLongCastle(self, truth_val): self.can_castle_long = truth_val
    def setValidMoves(self, board):
        self.valid_moves = []
        
        for dx, dy in self.directions:

            # check is within the board
            if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                board_pos = board[self.pos_y + dy][self.pos_x + dx]
                
                # check move does not put king in check
                if not board_pos or (board_pos and board_pos.getColor() != self.color):
                    self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))
    
    def setHasMoved(self):
        self.hasMoved = True

    def canCastle(self, board, turn):

        # expected coords for all pieces
        long_rook = (0,0) if turn == 'white' else (0,7)
        short_rook = (7,0) if turn == 'white' else (7,7)
        king = (4,0) if turn == 'white' else (4,7)

        # icon for rook piece
        rook_icon = '♖' if turn == 'black' else '♜'

        # unpack all of the expected coords into their x,y counter-parts for easy indexing
        king_x, king_y = king
        short_x, short_y = short_rook
        long_x, long_y = long_rook

        # initially set can castle to true for each type of castle. they will be set to false if
        # the king cannot castle that way.
        self.can_castle_long = True
        self.can_castle_short = True

        # if king not in correct position, king cannot castle
        if self.pos_x != king_x or self.pos_y != king_y or self.hasMoved: 
            self.can_castle_long = False
            self.can_castle_short = False

        # if short rook not in correct position, king cannot castle
        if not board[short_y][short_x] or (board[short_y][short_x].getIcon() != rook_icon or board[short_y][short_x].getHasMoved()): 
            self.can_castle_short = False

        # if king/rook is blocked, king cannot castle
        for i in [5,6]: 
            if board[king_y][i]: 
                self.can_castle_short = False

        # if long rook not in correct position, king cannot castle
        if not board[long_y][long_x] or (board[long_y][long_x].getIcon() != rook_icon or board[long_y][long_x].getHasMoved()): 
            self.can_castle_long = False

        # if king/rook is blocked, king cannot castle
        for i in [1,2,3]: 
            if board[king_y][i]: self.can_castle_long = False
    
    

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
        self.valid_moves = []

        for direction in self.directions:

            for dx, dy in direction:

                # check is within the board
                if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                    board_pos = board[self.pos_y + dy][self.pos_x + dx]
                    
                    if not board_pos or (board_pos and board_pos.getColor() != self.color):
                        self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))
                        if board_pos and board_pos.getColor() != self.color: break
                    else: break

class Rook(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265C' if color == 'white' else '\u2656'
        self.directions = [ [(0,1),(0,2),(0,3),(0,4),(0,5),(0,6),(0,7)], 
                            [(-1,0),(-2,0),(-3,0),(-4,0),(-5,0),(-6,0),(-7,0)],       
                            [(1,0),(2,0),(3,0),(4,0),(5,0),(6,0),(7,0)],
                            [(0,-1),(0,-2),(0,-3),(0,-4),(0,-5),(0,-6),(0,-7)] ]
        self.can_castle = True
        self.hasMoved = False

    def getIcon(self): return self.icon

    def getHasMoved(self): return self.hasMoved

    def setValidMoves(self, board):
        self.valid_moves = []

        for direction in self.directions:

            for dx, dy in direction:

                # check is within the board
                if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                    board_pos = board[self.pos_y + dy][self.pos_x + dx]
                    
                    # check move does not put king in check
                    if not board_pos or (board_pos and board_pos.getColor() != self.color):
                        self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))
                        if board_pos and board_pos.getColor() != self.color: break
                    else: break
    
    def setHasMoved(self):
        self.hasMoved = True

class Bishop(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265D' if color == 'white' else '\u2657'
        self.directions = [ [(-1,1),(-2,2),(-3,3),(-4,4),(-5,5),(-6,6),(-7,7)],
                            [(1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7)],
                            [(-1,-1),(-2,-2),(-3,-3),(-4,-4),(-5,-5),(-6,-6),(-7,-7)],
                            [(1,-1),(2,-2),(3,-3),(4,-4),(5,-5),(6,-6),(7,-7)] ]

    def getIcon(self): return self.icon

    def setValidMoves(self, board):
        self.valid_moves = []

        for direction in self.directions:

            for dx, dy in direction:

                # check is within the board
                if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                    board_pos = board[self.pos_y + dy][self.pos_x + dx]
                    
                    # check move does not put king in check
                    if not board_pos or (board_pos and board_pos.getColor() != self.color):
                        self.valid_moves.append((self.pos_x + dx, self.pos_y + dy))
                        if board_pos and board_pos.getColor() != self.color: break
                    else: break

class Knight(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265E' if color == 'white' else '\u2658'
        self.directions = [      (-1,2),  (1,2),
                           (-2,1),              (2,1),
                           (-2,-1),             (2,-1),
                                 (-1,-2),  (1,-2) ]

    def getIcon(self): return self.icon

    def setValidMoves(self, board):
        self.valid_moves = []
        
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
        self.directions = ([(0,-2),(-1,-1),(0,-1),(1,-1)] if color == 'black' 
                           else [(0,2),(-1,1),(0,1),(1,1)])
        
        # pawn can initially jump 2 squares before moving
        self.initial_jump = True 
        self.enPassantLeft, self.enPassantRight = False, False

    def getIcon(self): return self.icon

    def setValidMoves(self, board):
        self.valid_moves = []
        
        for idx, direction in enumerate(self.directions):

            dx, dy = direction
            new_x, new_y = self.pos_x + dx, self.pos_y + dy

            if 0 <= new_x < 8 and 0 <= new_y < 8:

                board_pos = board[new_y][new_x]
                prev_pos = (board[new_y+1][new_x] if self.color == 'black' 
                            else board[new_y-1][new_x])

                # if idx 0 (2 square jump), and initial jump variable is true 
                # and the two square required in jump are not blocked 
                # (board_pos and prev_pos), 2 square jump is valid move
                if (idx == 0 and self.initial_jump and 
                    (not board_pos and not prev_pos)):
                    self.valid_moves.append( (new_x, new_y) )

                # if idx 1 or 3 (pawn takes), and the board has a piece that 
                # is not the color of the pawn, pawn takes is a valid move.
                # on top of this, if the en passant value corresponding to
                # the given idx is set, this is also a valid move.
                elif (idx == 1 or idx == 3):
                    
                    if self.debug_mode:
                        print(f"""({self.pos_x},{self.pos_y}) ({idx}): \nleft: {self.enPassantLeft}\nright: {self.enPassantRight}\n""")
                    
                    # first line handles normal valid move, 2nd and 3rd handles
                    # en passants
                    if ((board_pos and board_pos.getColor() != self.color)
                        or (self.enPassantLeft and idx == 1)
                            or (self.enPassantRight and idx == 3)): 
                            if self.debug_mode:
                                print("setting!")
                            self.valid_moves.append( (new_x, new_y) )
                    
                # if idx 2 (pawn takes step forward) and the spot in front of
                # the pawn is not blocked, step forward is valid move
                elif idx == 2 and not board_pos:
                    self.valid_moves.append( (new_x, new_y) )
    
    def getEnPassant(self): return (self.enPassantLeft, self.enPassantRight)
    
    def setEnPassant(self, isLeft, clear=0):
        
        if clear:
            self.enPassantLeft, self.enPassantRight = False
        
        else:
            if isLeft: self.enPassantLeft = True
            else:      self.enPassantRight = True
    
    def setHasMoved(self):
        self.initial_jump = False
        