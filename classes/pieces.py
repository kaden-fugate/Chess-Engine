# piece will have a color as well as an array of valid moves. 
# we will have child classes for specific types of pieces such
# as king or pawn.
class Piece:
    
    def __init__(self, pos_x, pos_y, color):
        self.color = color
        self.validMoves = []
        self.pos_x = pos_x
        self.pos_y = pos_y
    
    def getColor(self):
        return self.color

    def getIcon():
        pass

    def setValidMoves(self, board):
        
        for dx, dy in self.directions:

            # check is within the board
            if 0 <= self.pos_x + dx < 8 and 0 <= self.pos_y + dy < 8:

                board_pos = board[self.pos_y + dy][self.pos_x + dx]
                
                # check move does not put king in check
                if not board_pos or (board_pos and board_pos.getColor() != self.color):
                    self.validMoves.append((self.pos_x + dx, self.pos_y + dy))
    
    def getValidMoves(self):
        return self.validMoves

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
                        self.validMoves.append((self.pos_x + dx, self.pos_y + dy))
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
                        self.validMoves.append((self.pos_x + dx, self.pos_y + dy))
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
                        self.validMoves.append((self.pos_x + dx, self.pos_y + dy))
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

class Pawn(Piece):

    def __init__(self, pos_x, pos_y, color):
        super().__init__(pos_x, pos_y, color)
        self.icon = '\u265F' if color == 'white' else '\u2659'
        self.directions = [       (0,2),
                           (-1,1),(0,1),(1,1)] if color == 'black' else [(0,-2), (-1,-1),(0,-1),(1,-1)]

    def getIcon(self): return self.icon