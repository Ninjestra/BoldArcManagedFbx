#pragma once
namespace BoldarcManagedFbx
{
	public value struct Vector3
	{
	public:

		property double X;
		property double Y;
		property double Z;

		Vector3( double inX, double inY, double inZ )
		{
			X = inX;
			Y = inY;
			Z = inZ;
		}

		FbxDouble3 ToFbxDouble3()
		{
			return FbxDouble3( X, Y, Z );
		}

		FbxVector4 ToFbxVector4()
		{
			return FbxVector4( X, Y, Z );
		}

	};
}
