from pieces import Piece

# Square has coordinates as well as a piece
class Square:

    def __init__(self, pos_x, pos_y, piece):
        self.pos_x = pos_x
        self.pos_y = pos_y
        self.piece = piece
    
    def setPiece(self, piece):
        self.piece = piece
    
    def printPiece(self):
        if not self.piece: print("    | ", end="")
        else: print(f" {self.piece.getIcon()}  | ", end="")