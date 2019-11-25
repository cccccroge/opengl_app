#include "FrameBuffer.h"
#include "../global.h"
#include <iostream>


FrameBuffer::FrameBuffer()
{
    // setup screen vao and vbo
    float screenVertices[] = { 
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, 
        GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
        (const void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
        (const void *)(2 * sizeof(float)));

    // setup frame buffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // tbo: color output to a texture
    glGenTextures(1, &tbo);
    glBindTexture(GL_TEXTURE_2D, tbo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT, 0,
        GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
        GL_TEXTURE_2D, tbo, 0);

    // rbo: depth and stencil test
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 
        MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
        GL_RENDERBUFFER, rbo);

    // check if valid
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "invalid frame buffer" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}


void FrameBuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBuffer::useScreenVertexTexture()
{
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tbo);
}