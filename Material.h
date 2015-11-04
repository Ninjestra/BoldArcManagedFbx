#pragma once
using namespace System;

namespace BoldarcManagedFbx
{
	public value struct Material
	{
		property String^ Name;

		property Byte Red;
		property Byte Green;
		property Byte Blue;

		property int Shininess;
		property int Smoothness;
		property double Transparency;

		Material( String^ inName )
		{
			Name = inName;
		}
	};
}