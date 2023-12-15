# piece will have a color as well as an array of valid moves. 
# we will have child classes for specific types of pieces such
# as king or pawn.
class Piece:
    
    def __init__(self, color):
        self.color = color
        self.valid_moves = None
    
    def printIcon():
        pass

    def getValidMoves():
        pass

class King(Piece):

    def __init__(self, color):
        super().__init__(color)
        self.icon = '\u265A' if color == 'white' else '\u2654'

    def getIcon(self): return self.icon

class Queen(Piece):

    def __init__(self, color):
        super().__init__(color)
        self.icon = '\u265B' if color == 'white' else '\u2655'

    def getIcon(self): return self.icon

class Rook(Piece):

    def __init__(self, color):
        super().__init__(color)
        self.icon = '\u265C' if color == 'white' else '\u2656'

    def getIcon(self): return self.icon

class Bishop(Piece):

    def __init__(self, color):
        super().__init__(color)
        self.icon = '\u265D' if color == 'white' else '\u2657'

    def getIcon(self): return self.icon

class Knight(Piece):

    def __init__(self, color):
        super().__init__(color)
        self.icon = '\u265E' if color == 'white' else '\u2658'

    def getIcon(self): return self.icon

class Pawn(Piece):

    def __init__(self, color):
        super().__init__(color)
        self.icon = '\u265F' if color == 'white' else '\u2659'

    def getIcon(self): return self.icon