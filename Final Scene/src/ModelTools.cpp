#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	Vect A;
	Vect B;
	Vect C;
	Vect u;
	Vect v;
	Vect n;


	A.set(0.5f, 0.5f, 0.5f);
	B.set(-0.5f, 0.5f, 0.5f);
	C.set(-0.5f, -0.5f, 0.5f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, n, Colors::Red);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, n, Colors::Red);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, n, Colors::Red);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);


	A.set(-0.5f, 0.5f, -0.5f);
	B.set(-0.5f, -0.5f, -0.5f);
	C.set(0.5f, -0.5f, -0.5f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(0.5f, 0.5f, -0.5f, 0, 0, -n, Colors::Red);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, -n, Colors::Red);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, -n, Colors::Red);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, -n, Colors::Red);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);


	A.set(0.5f, 0.5f, -0.5f);
	B.set(0.5f, 0.5f, 0.5f);
	C.set(0.5f, -0.5f, 0.5f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, n, Colors::Red);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, n, Colors::Red);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, n, Colors::Red);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);


	A.set(-0.5f, 0.5f, 0.5f);
	B.set(-0.5f, 0.5f, -0.5f);
	C.set(-0.5f, -0.5f, -0.5f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, n, Colors::Red);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, n, Colors::Red);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, n, Colors::Red);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);


	A.set(0.5f, 0.5f, -0.5f);
	B.set(-0.5f, 0.5f, -0.5f);
	C.set(-0.5f, 0.5f, 0.5f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, n, Colors::Red);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, n, Colors::Red);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, n, Colors::Red);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);


	A.set(0.5f, -0.5f, 0.5f);
	B.set(-0.5f, -0.5f, 0.5f);
	C.set(-0.5f, -0.5f, -0.5f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, n, Colors::Red);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, n, Colors::Red);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, n, Colors::Red);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateSkyBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	float size = 25.0f;


	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind + 0].set(size, size, size, 0.5, 0.333);
	pVerts[vind + 1].set(-size, size, size, 0.75, 0.333);
	pVerts[vind + 2].set(-size, -size, size, 0.75, 0.667);
	pVerts[vind + 3].set(size, -size, size, 0.5, 0.65);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, size, -size, 0.25, 0.333);
	pVerts[vind + 1].set(-size, size, -size, 0, 0.333);
	pVerts[vind + 2].set(-size, -size, -size, 0, 0.66);
	pVerts[vind + 3].set(size, -size, -size, 0.25, 0.66);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, size, -size, 0.25, 0.333);
	pVerts[vind + 1].set(size, size, size, 0.5, 0.333);
	pVerts[vind + 2].set(size, -size, size, 0.5, 0.65);
	pVerts[vind + 3].set(size, -size, -size, 0.25, 0.66);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(-size, size, size, 0.75, 0.335);
	pVerts[vind + 1].set(-size, size, -size, 1.0, 0.335);
	pVerts[vind + 2].set(-size, -size, -size, 1.0, 0.665);
	pVerts[vind + 3].set(-size, -size, size, 0.75, 0.665);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, size, -size, 0.5, 0.0);
	pVerts[vind + 1].set(-size, size, -size, 0.75, 0.0);
	pVerts[vind + 2].set(-size, size, size, 0.75, 0.333);
	pVerts[vind + 3].set(size, size, size, 0.5, 0.333);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind + 0].set(size, -size, size, 0.5, 0.6667);
	pVerts[vind + 1].set(-size, -size, size, 0.72, 0.666);
	pVerts[vind + 2].set(-size, -size, -size, 0.72, 0.99);
	pVerts[vind + 3].set(size, -size, -size, 0.5, 0.99);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);
}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	float size = 25;

	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;

	Vect A;
	A.set(0.0f, 1.0f, 0.0f);
	Vect B;
	B.set(-1.0f, -1.0f, 1.0f);
	Vect C;
	C.set(1.0f, -1.0f, 1.0f);

	Vect u = B - A;
	Vect v = C - A;
	Vect n = (u.cross(v)).getNorm();

	pVerts[vind + 0].set(0.0f, size, 0.0f, 0.5f, 0, n, Colors::Blue);
	pVerts[vind + 1].set(-size, -size, size, 0, 1.0f, n, Colors::Blue);
	pVerts[vind + 2].set(size, -size, size, 1, 1, n, Colors::Blue);
	pTriList[tind].set(vind, vind + 1, vind + 2);


	A.set(0.0f, 1.0f, 0.0f);
	B.set(-1.0f, -1.0f, -1.0f);
	C.set(1.0f, -1.0f, -1.0f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Back
	vind += 3;
	tind += 1;
	pVerts[vind + 0].set(0.0f, size, 0.0f, 0.5, 0.0f, -n, Colors::Blue);
	pVerts[vind + 1].set(size, -size, -size, 1.0f, 1.0f, -n, Colors::Blue);
	pVerts[vind + 2].set(-size, -size, -size, 0.0f, 1.0f, -n, Colors::Blue);
	pTriList[tind].set(vind, vind + 1, vind + 2);


	A.set(0.0f, 1.0f, 0.0f);
	B.set(1.0f, -1.0f, 1.0f);
	C.set(1.0f, -1.0f, -1.0f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Left
	vind += 3;
	tind += 1;
	pVerts[vind + 0].set(0.0f, size, 0.0f, 0.5f, 0.0f, n, Colors::Red);
	pVerts[vind + 1].set(size, -size, size, 0.0f, 1.0f, n, Colors::Red);
	pVerts[vind + 2].set(size, -size, -size, 1.0f, 1.0f, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);


	A.set(0.0f, 1.0f, 0.0f);
	B.set(-1.0f, -1.0f, -1.0);
	C.set(-1.0f, -1.0f, 1.0f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Right
	vind += 3;
	tind += 1;
	pVerts[vind + 0].set(0.0f, size, 0.0f, 0.5f, 0.0f, n, Colors::Red);
	pVerts[vind + 1].set(-size, -size, -1.0, 0.0f, 1.0f, n, Colors::Red);
	pVerts[vind + 2].set(-size, -size, size, 1.0f, 1.0f, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);

	//// Top  -  No Top


	A.set(-1.0f, -1.0f, 1.0f);
	B.set(-1.0f, -1.0f, -1.0f);
	C.set(1.0f, -1.0f, -1.0f);
	u = B - A;
	v = C - A;
	n = (u.cross(v)).getNorm();

	// Bottom
	vind += 3;
	tind += 1;
	pVerts[vind + 0].set(-size, -size, size, 0.0f, 0.0f, n, Colors::Red);
	pVerts[vind + 1].set(-size, -size, -size, 0.0f, 1.0f, n, Colors::Red);
	pVerts[vind + 2].set(size, -size, -size, 1.0f, 1.0f, n, Colors::Red);
	pVerts[vind + 3].set(size, -size, size, 1.0f, 0.0f, n, Colors::Red);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	float size = 5.0f;

	nverts = vslice * (hslice + 1) + 2;
	ntri = vslice * hslice * 2;
	pVerts = new StandardVertex[nverts];
	pTriList = new TriangleByIndex[ntri];

	Vect* texcoords = new Vect[nverts];

	// North pole.
	pVerts[0].set(0.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	// South pole.
	pVerts[nverts - 1].set(0.0f, -1.0f, 0.0f, 0.0f, 0.0f);

	// +1.0f because there's a gap between the poles and the first parallel.
	float latitude_step = 1.0f / (hslice + 1.0f);
	float longitude_step = 1.0f / (vslice);

	// start writing new vertices at position 1
	int vertex = 1;
	for (int latitude = 0; latitude < hslice; latitude++) {

		for (int longitude = 0; longitude <= vslice; longitude++) {
			// Scale coordinates into the 0...1 texture coordinate range,
			// with north at the top (y = 1).
			texcoords[vertex] = Vect(longitude * longitude_step,
				1.0f - (latitude + 1) * latitude_step,
				0.0f, 0.0f
			);


			// Convert to spherical coordinates:
			// theta is a longitude angle (around the equator) in radians.
			// phi is a latitude angle (north or south of the equator).
			float theta = texcoords[vertex].X() * 2.0f * 3.14159f;
			float phi = (texcoords[vertex].Y() - 0.5f) * 3.14159f;

			// This determines the radius of the ring of this line of latitude.
			// It's widest at the equator, and narrows as phi increases/decreases.
			float c = cosf(phi);

			// Usual formula for a vector in spherical coordinates.
			// You can exchange x & z to wind the opposite way around the sphere.

			float x = c * cosf(theta);
			float y = sinf(phi);
			float z = c * sinf(theta);

			pVerts[vertex].set(
				x * size, y * size, z * size,
				texcoords[vertex].X(),
				texcoords[vertex].Y(),
				x, y, z
			);

			// Proceed to the next vertex.
			vertex++;
		}
	}

	int triangle = 0;

	for (int face = 0; face < vslice; face++) {
		pTriList[triangle++].set(0, face + 2, face + 1);
	}

	// Each row has one more unique vertex than there are lines of longitude,
	// since we double a vertex at the texture seam.
	int row_length = vslice + 1;

	for (int latitude = 0; latitude < hslice - 1; latitude++) {
		// Plus one for the pole.
		int row_start = latitude * row_length + 1;
		for (int longitude = 0; longitude < vslice; longitude++) {
			int first_corner = row_start + longitude;

			// First triangle of quad: Top-Left, Bottom-Left, Bottom-Right
			pTriList[triangle++].set(first_corner,
				first_corner + row_length + 1,
				first_corner + row_length);

			// Second triangle of quad: Top-Left, Bottom-Right, Top-Right
			pTriList[triangle++].set(first_corner,
				first_corner + 1,
				first_corner + row_length + 1);
		}
	}

	int south_pole = nverts - 1;
	int bottom_row = (hslice - 1) * row_length + 1;

	for (int face = 0; face < vslice; face++) {
		pTriList[triangle++].set(south_pole, bottom_row + face,
			bottom_row + face + 1);
	}

	delete[] texcoords;
}
