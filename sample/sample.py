# from OpenGL.extensions import alternate
# from OpenGL.GL import *
# from OpenGL.GL.ARB.multitexture import *
# from OpenGL.GLU import *
# from OpenGL.GLUT import *
#
#
# class TestTexture():
#
#     def __init__(self):
#         self.window_width = 800
#         self.window_height = 800
#
#     def init(self):
#         glClearColor(0.0, 0.0, 0.0, 0.0)
#         glMatrixMode(GL_PROJECTION)
#         glLoadIdentity()
#         glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0)
#         glMatrixMode(GL_MODELVIEW)
#         glLoadIdentity()
#         glEnable(GL_TEXTURE_2D)
#
#
#     def display(self):
#         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
#         glLoadIdentity()
#
#         glBegin(GL_TRIANGLES)
#         glVertex3f(-1.0, 0.0, 0.0)
#         glVertex3f(1.0, 0.0, 0.0)
#         glVertex3f(0.0, 1.0, 0.0)
#         glEnd()
#
#         glFlush()
#         glutSwapBuffers()
#
#     def reshape(self, w, h):
#         self.window_width = w
#         self.window_height = h
#         glViewport(0, 0, self.window_width, self.window_height)
#
#     def animate(self):
#         glutPostRedisplay()
#
#     def visible(self, vis):
#         if (vis == GLUT_VISIBLE):
#             glutIdleFunc(self.animate)
#         else:
#             glutIdleFunc(0)
#
#     def key_pressed(self, *args):
#         if args[0] == b"\x1b":
#             sys.exit()
#
#     def run(self):
#         glutInit(sys.argv)
#         glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH)
#         glutInitWindowSize(self.window_width, self.window_height)
#         glutInitWindowPosition(800, 100)
#         glutCreateWindow(b'MCVE')
#         glutDisplayFunc(self.display)
#         glutReshapeFunc(self.reshape)
#         glutIdleFunc(self.animate)
#         glutVisibilityFunc(self.visible)
#         glutKeyboardFunc(self.key_pressed)
#         glScaled(2, 1, 1)
#         glScaled(1, 2, 2)
#         self.init()
#         glutMainLoop()
#
# if __name__ == "__main__":
#     TestTexture().run()

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *


def drawFunc():
    glClear(GL_COLOR_BUFFER_BIT)
    # glRotatef(1, 0, 1, 0)
    glutWireTeapot(0.5)
    glScaled(2, 1, 1)
    glScaled(1, 2, 2)
    glFlush()


glutInit()
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
glutInitWindowSize(400, 400)
glutCreateWindow("First")
glutDisplayFunc(drawFunc)
# glutIdleFunc(drawFunc)
glutMainLoop()