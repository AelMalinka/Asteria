/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_ARMOR_INC
#	define ENTROPY_ASTERIA_ARMOR_INC

#	include "Equipment.hh"

	namespace Entropy
	{
		namespace Asteria
		{
			class Armor :
				public Equipment
			{
				public:
					enum class Type
					{
						None,
						Light,
						Heavy
					};
				public:
					Armor(const std::string &, const std::shared_ptr<Theia::GL::Texture> &, const Type &, const Template &);
					Armor(const Armor &);
					Armor(Armor &&);
					virtual ~Armor();
					const Type &Which() const;
				private:
					Type _type;
			};

			ENTROPY_ERROR_INFO(ArmorTypeInfo, Armor::Type);
		}
	}

#endif
