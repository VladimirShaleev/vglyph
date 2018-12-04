/* vglyph - library for visualize glyphs
 *
 * File: vglyph-matrix.h
 * Copyright (C) 2018 Shaleev Vladimir
 */

#ifndef VGLYPH_MATRIX_H
#define VGLYPH_MATRIX_H

#include "vglyph-api.h"

/* vglyph_matrix_t holds an affine
 * transformation: scale, rotation, shear.
 * The transformation of (x, y) is given by:
 *
 *   result_x = xx * x + xy * y + x0
 *   result_y = yx * x + yy * y + y0;
 */

typedef struct _vglyph_matrix
{
    vglyph_float32_t xx; vglyph_float32_t yx;
    vglyph_float32_t xy; vglyph_float32_t yy;
    vglyph_float32_t x0; vglyph_float32_t y0;
} vglyph_matrix_t;

static inline vglyph_matrix_t*
_vglyph_matrix_init(vglyph_matrix_t* result,
                    vglyph_float32_t xx,
                    vglyph_float32_t yx,
                    vglyph_float32_t xy,
                    vglyph_float32_t yy,
                    vglyph_float32_t x0,
                    vglyph_float32_t y0)
{
    assert(result);

    result->xx = xx;
    result->yx = yx;
    result->xy = xy;
    result->yy = yy;
    result->x0 = x0;
    result->y0 = y0;

    return result;
}

static inline vglyph_matrix_t*
_vglyph_matrix_identity(vglyph_matrix_t* result)
{
    assert(result);

    return _vglyph_matrix_init(result,
                               1.0f, 0.0f,
                               0.0f, 1.0f,
                               0.0f, 0.0f);
}

static inline vglyph_matrix_t*
_vglyph_matrix_init_translate(vglyph_matrix_t* result,
                              vglyph_float32_t tx,
                              vglyph_float32_t ty)
{
    assert(result);

    return _vglyph_matrix_init(result,
                               1.0f, 0.0f,
                               0.0f, 1.0f,
                               tx,   ty);
}

static inline vglyph_matrix_t*
_vglyph_matrix_init_scale(vglyph_matrix_t* result,
                          vglyph_float32_t sx,
                          vglyph_float32_t sy)
{
    assert(result);

    return _vglyph_matrix_init(result,
                               sx,   0.0f,
                               0.0f, sy,
                               0.0f, 0.0f);
}

static inline vglyph_matrix_t*
_vglyph_matrix_init_rotate(vglyph_matrix_t* result,
                           vglyph_float32_t radians)
{
    assert(result);

    vglyph_float32_t s = (vglyph_float32_t)sin((double)radians);
    vglyph_float32_t c = (vglyph_float32_t)cos((double)radians);

    return _vglyph_matrix_init(result,
                                c,   s,
                               -s,   c,
                               0.0f, 0.0f);
}

static inline vglyph_matrix_t*
_vglyph_matrix_multiply(vglyph_matrix_t* result,
                        const vglyph_matrix_t* mat1,
                        const vglyph_matrix_t* mat2)
{
    assert(result);
    assert(mat1);
    assert(mat2);

    vglyph_matrix_t r;

    r.xx = mat1->xx * mat2->xx + mat1->yx * mat2->xy;
    r.yx = mat1->xx * mat2->yx + mat1->yx * mat2->yy;
                                          
    r.xy = mat1->xy * mat2->xx + mat1->yy * mat2->xy;
    r.yy = mat1->xy * mat2->yx + mat1->yy * mat2->yy;
                                           
    r.x0 = mat1->x0 * mat2->xx + mat1->y0 * mat2->xy + mat2->x0;
    r.y0 = mat1->x0 * mat2->yx + mat1->y0 * mat2->yy + mat2->y0;

    *result = r;
    return result;
}

static inline vglyph_matrix_t*
_vglyph_matrix_scalar_multiply(vglyph_matrix_t* result,
                               const vglyph_matrix_t* mat,
                               vglyph_float32_t scalar)
{
    assert(result);
    assert(mat);

    result->xx = mat->xx * scalar;
    result->yx = mat->yx * scalar;

    result->xy = mat->xy * scalar;
    result->yy = mat->yy * scalar;

    result->x0 = mat->x0 * scalar;
    result->y0 = mat->y0 * scalar;

    return result;
}

static inline vglyph_matrix_t*
_vglyph_matrix_scalar_divide(vglyph_matrix_t* result,
                             const vglyph_matrix_t* mat,
                             vglyph_float32_t scalar)
{
    assert(result);
    assert(mat);

    return _vglyph_matrix_scalar_multiply(result, mat, 1.0f / scalar);
}

static inline vglyph_float32_t
_vglyph_matrix_determinant(const vglyph_matrix_t* mat)
{
    return mat->xx * mat->yy - mat->yx * mat->xy;
}

static inline vglyph_matrix_t*
_vglyph_matrix_adjoint(vglyph_matrix_t* result,
                       const vglyph_matrix_t* mat)
{
    assert(result);
    assert(mat);

    return _vglyph_matrix_init(result,
                               mat->yy, -mat->yx,
                              -mat->xy,  mat->xx,
                               mat->xy * mat->y0 - mat->yy * mat->x0, 
                               mat->yx * mat->x0 - mat->xx * mat->y0);
}

static inline vglyph_bool_t
_vglyph_matrix_is_invertible(const vglyph_matrix_t* mat)
{
    assert(mat);

    vglyph_float32_t det = _vglyph_matrix_determinant(mat);
    return isfinite(det) && det != 0.0f;
}

static inline vglyph_matrix_t*
_vglyph_matrix_invert(vglyph_matrix_t* result,
                      const vglyph_matrix_t* mat)
{
    assert(result);
    assert(mat);

    vglyph_matrix_t m = *mat;

    if (m.xy == 0.0f && m.yx == 0.0f)
    {
        m.x0 = -m.x0;
        m.y0 = -m.y0;

        if (m.xx != 1.0f) 
        {
            if (m.xx == 0.0f)
                return NULL;

            m.xx = 1.0f / m.xx;
            m.x0 *= m.xx;
        }

        if (m.yy != 1.0f) 
        {
            if (m.yy == 0.0f)
                return NULL;

            m.yy = 1.0f / m.yy;
            m.y0 *= m.yy;
        }

        *result = m;
        return result;
    }

    vglyph_float32_t det = _vglyph_matrix_determinant(&m);

    if (!isfinite(det) || det == 0.0f)
        return NULL;

    _vglyph_matrix_adjoint(&m, &m);
    
    return _vglyph_matrix_scalar_divide(result, &m, det);
}

static inline vglyph_matrix_t*
_vglyph_matrix_translate(vglyph_matrix_t* result,
                         const vglyph_matrix_t* mat,
                         vglyph_float32_t tx,
                         vglyph_float32_t ty)
{
    assert(result);
    assert(mat);

    vglyph_matrix_t mat2;
    _vglyph_matrix_init_translate(&mat2, tx, ty);
    
    return _vglyph_matrix_multiply(result, &mat2, mat);
}

static inline vglyph_matrix_t*
_vglyph_matrix_scale(vglyph_matrix_t* result,
                     const vglyph_matrix_t* mat,
                     vglyph_float32_t sx,
                     vglyph_float32_t sy)
{
    assert(result);
    assert(mat);

    vglyph_matrix_t mat2;
    _vglyph_matrix_init_scale(&mat2, sx, sy);

    return _vglyph_matrix_multiply(result, &mat2, mat);
}

static inline vglyph_matrix_t*
_vglyph_matrix_rotate(vglyph_matrix_t* result,
                     const vglyph_matrix_t* mat,
                     vglyph_float32_t radians)
{
    assert(result);
    assert(mat);

    vglyph_matrix_t mat2;
    _vglyph_matrix_init_rotate(&mat2, radians);

    return _vglyph_matrix_multiply(result, &mat2, mat);
}

static inline vglyph_point_t*
_vglyph_matrix_transform_point(vglyph_point_t* result,
                               const vglyph_matrix_t* mat,
                               const vglyph_point_t* point)
{
    assert(result);
    assert(mat);
    assert(point);

    vglyph_point_t r;

    r.x = mat->xx * point->x + mat->xy * point->y + mat->x0;
    r.y = mat->yx * point->x + mat->yy * point->y + mat->y0;

    *result = r;
    return result;
}

#endif
