# 87.25
# 326.58
# 36.14
# Isosceles
# True
# (16.67, 27.0)
# Triangle(A(5,30),B(27,43),C(18,8))
import math
class Triangle:
    Ax = 0
    Ay = 0
    Bx = 0
    By = 0
    Cx = 0
    Cy = 0
    AB = 0
    AC = 0
    BC = 0
    def __init__(self,pAx,pAy,pBx,pBy,pCx,pCy):
        self.Ax = pAx
        self.Ay = pAy
        self.Bx = pBx
        self.By = pBy
        self.Cx = pCx
        self.Cy = pCy
        self.AB = self.distancePoint(self.Ax,self.Ay,self.Bx,self.By)
        self.AC = self.distancePoint(self.Ax,self.Ay,self.Cx,self.Cy)
        self.BC = self.distancePoint(self.Bx,self.By,self.Cx,self.Cy)
    def __str__(self):
        return "Triangle(A(%d,%d),B(%d,%d),C(%d,%d))" %(self.Ax,self.Ay,self.Bx,self.By,self.Cx,self.Cy)
    def distancePoint(self,Ax,Ay,Bx,By):
        return math.sqrt(((Ax-Bx)**2)+((Ay-By)**2))
    def Perimeter(self):
        return round(self.AB + self.AC + self.BC,2)
    def Area(self):
        s = self.Perimeter() / 2
        return round(math.sqrt(s*(s-self.AB)*(s-self.AC)*(s-self.BC)),2)
    def LongestSide(self):
        max = self.AB
        if(self.AC > max):
            max = self.AC
        if(self.BC > max):
            max = self.BC
        return round(max,2)
    def ClassifyBySideLength(self):
        if(self.AB == self.AC and self.AB == self.BC):
            return 'Equilateral'
        elif(self.AB == self.AC or self.AB == self.BC or self.AC == self.BC):
            return 'Isosceles'
        else:
            return 'Scalene'
    def IsRightTriangle(self):
        if self.AB > self.BC and self.AB > self.AC:
            a = self.BC
            b = self.AC
            c = self.AB
        elif self.AC > self.BC and self.AC > self.AB:
            a = self.AB
            b = self.BC
            c = self.AC
        else:
            a = self.AB
            b = self.AC
            c = self.BC
        leftSide = round(a**2+b**2,2)
        rightSide = round(c**2,2)
        return leftSide == rightSide
    def Centroid(self):
        return round((self.Ax+self.Bx+self.Cx)/3,2), round((self.Ay+self.By+self.Cy)/3,2)
class RightTriangle(Triangle):
    def __init__(self,pAx,pAy,pBx,pBy,pCx,pCy):
        Triangle.__init__(self,pAx,pAy,pBx,pBy,pCx,pCy)
    def Sin(self,angle):
        if(angle=='A'):
            return round(self.BC/self.LongestSide(),2)
        elif(angle=='B'):
            return round(self.AC/self.LongestSide(),2)   
        elif(angle=='C'):
            return round(self.AB/self.LongestSide(),2)  
        else:
            return -1
    def Cos(self,angle):
        h = ''
        if(round(self.BC,2)==self.LongestSide()):
            h = 'A'
        elif(round(self.AB,2)==self.LongestSide()):
            h = 'C'
        else:
            h = 'B'
        if(angle=='A'):
            if(h=='A'):
               return 0
            else:
                if(h=='B'):
                    return round(self.AB/self.AC,2) 
                else:
                    return round(self.AC/self.AB,2)
        elif(angle=='B'):
            if(h=='B'):
               return 0
            else:
                if(h=='A'):
                    return round(self.AB /self.BC,2) 
                else:
                    return round(self.BC/self.AB,2) 
        elif(angle=='C'):
            if(h=='C'):
               return 0
            else:
                if(h=='A'):
                    return round(self.AC /self.BC,2) 
                else:
                    return round(self.BC/self.AC,2) 
        else:
            return -1
    def Tan(self,angle):
        h = ''
        if(round(self.BC,2)==self.LongestSide()):
            h = 'A'
        elif(round(self.AB,2)==self.LongestSide()):
            h = 'C'
        else:
            h = 'B'
        if(angle=='A'):
            if(h=='A'):
               return math.inf
            else:
                if(h=='B'):
                    return round(self.BC/self.AB,2) 
                else:
                    return round(self.BC/self.AC,2)
        elif(angle=='B'):
            if(h=='B'):
               return math.inf
            else:
                if(h=='A'):
                    return round(self.AC /self.AB,2) 
                else:
                    return round(self.AC/self.BC,2) 
        elif(angle=='C'):
            if(h=='C'):
               return math.inf
            else:
                if(h=='A'):
                    return round(self.AB /self.AC,2) 
                else:
                    return round(self.AB/self.BC,2) 
        else:
            return -1
def main():
    t = Triangle(5,30,27,43,18,8)
    print(t.Perimeter())
    print(t.Area())
    print(t.LongestSide())
    print(t.ClassifyBySideLength())
    print(t.IsRightTriangle())
    print(t.Centroid())
    print(t)
    rt = RightTriangle(0,0,0,1,1,1)
    print(rt.Cos('A'))
    print(rt.Sin('B'))
    print(rt.Sin('C'))
if __name__ == "__main__":
    main()