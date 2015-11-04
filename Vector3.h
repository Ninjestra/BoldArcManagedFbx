#pragma once
namespace BoldarcManagedFbx
{
	public value struct Vector3
	{

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

		Vector3 operator+(Vector3 inOther)
		{
			Vector3 _res;
			_res.X = X + inOther.X;
			_res.Y = Y + inOther.Y;
			_res.Z = Z + inOther.Z;

			return _res;
		}

		Vector3 operator-(Vector3 inOther)
		{
			Vector3 _res;
			_res.X = X - inOther.X;
			_res.Y = Y - inOther.Y;
			_res.Z = Z - inOther.Z;

			return _res;
		}

		Vector3 operator-(Vector3^ inOther)
		{
			Vector3 _res;
			_res.X = X - inOther->X;
			_res.Y = Y - inOther->Y;
			_res.Z = Z - inOther->Z;

			return _res;
		}

		Vector3 operator/(int inInt)
		{
			Vector3 _res;
			_res.X = X / inInt;
			_res.Y = Y / inInt;
			_res.Y = Y / inInt;

			return _res;
		}

		Vector3 operator*(double inDouble)
		{
			Vector3 _res;
			_res.X = X * inDouble;
			_res.Y = Y * inDouble;
			_res.Z = Z * inDouble;

			return _res;
		}
	};
}
