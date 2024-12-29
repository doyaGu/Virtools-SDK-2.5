/*************************************************************************/
/*	File : VxOBB.h														 */
/*	Author :  Aymeric Bard												 */
/*																		 */
/*	Virtools SDK 														 */
/*	Copyright (c) Virtools 2000, All Rights Reserved.					 */
/*************************************************************************/
#ifndef VxOBB_H
#define VxOBB_H

/**********************************************************
{filename:VxOBB}
Name: VxOBB

Summary: Class representation of a ray (an origin and a direction).

Remarks:
A Ray is defined by 2 VxVector and is used to represents
a ray in space (useful for intersection purposes.)

A VxOBB is defined as:

            class VxOBB
            {
            public:
                VxVector	m_Origin;
                VxVector	m_Direction;
            };




See Also : VxMatrix,VxVector
*********************************************************/
class VxOBB
{
public:
    // Ctors
    VxOBB() {}
    VxOBB(const VxBbox &box, const VxMatrix &mat) { Create(box, mat); }

    VxVector &GetCenter() { return m_Center; };
    const VxVector &GetCenter() const { return m_Center; }

    VxVector &GetAxis(int i) { return m_Axis[i]; }
    const VxVector &GetAxis(int i) const { return m_Axis[i]; }
    VxVector *GetAxes() { return m_Axis; }
    const VxVector *GetAxes() const { return m_Axis; };

    float &GetExtent(int i) { return m_Extents[i]; }
    const float &GetExtent(int i) const { return m_Extents[i]; }
    float *GetExtents() { return &m_Extents.x; }
    const float *GetExtents() const { return &m_Extents.x; }

    // Transform the ray into the other referential
    void Create(const VxBbox &box, const VxMatrix &mat)
    {
        VxVector v = box.GetCenter();
        Vx3DMultiplyMatrixVector(&m_Center, mat, &v);
        m_Axis[0] = *(VxVector *)&mat[0][0];
        m_Axis[1] = *(VxVector *)&mat[1][0];
        m_Axis[2] = *(VxVector *)&mat[2][0];
        m_Extents[0] = Magnitude(m_Axis[0]);
        m_Extents[1] = Magnitude(m_Axis[1]);
        m_Extents[2] = Magnitude(m_Axis[2]);
        m_Axis[0] /= m_Extents[0];
        m_Axis[1] /= m_Extents[1];
        m_Axis[2] /= m_Extents[2];
        m_Extents[0] *= 0.5f * (box.Max[0] - box.Min[0]);
        m_Extents[1] *= 0.5f * (box.Max[1] - box.Min[1]);
        m_Extents[2] *= 0.5f * (box.Max[2] - box.Min[2]);
    }

    // Center of the box
    VxVector m_Center;
    // Axis of the box
    VxVector m_Axis[3];
    // Extents of the box
    VxVector m_Extents;
};

#endif
