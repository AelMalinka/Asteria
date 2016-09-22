/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_WEAPON_INC
#	define ENTROPY_ASTERIA_WEAPON_INC

#	include "Equipment.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Weapon :
				public Equipment
			{
				public:
					enum class Type
					{
						None,
						Sword,
						Blunt,
						Bow,
						Thrown
					};
				public:
					Weapon(const std::string &, const Type &, const Template &);
					Weapon(const Weapon &);
					Weapon(Weapon &&);
					virtual ~Weapon();
					const Type &Which() const;
				private:
					Type _type;
			};

			ENTROPY_ERROR_INFO(WeaponTypeInfo, Weapon::Type);
		}
	}

#endif
