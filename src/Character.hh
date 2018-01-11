/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASTERIA_CHARACTER_INC
#	define ENTROPY_ASTERIA_CHARACTER_INC

#	include <Entropy/Hecate/Character.hh>

#	include "Exception.hh"

#	ifndef ENTROPY_ASTERIA_DEFAULT_MAX_DAMAGE
#		define ENTROPY_ASTERIA_DEFAULT_MAX_DAMAGE 10
#	endif

#	include "Character/Stats.hh"
#	include "Character/Skills.hh"
#	include "Character/Resources.hh"

#	include "Character/Weapon.hh"
#	include "Character/Armor.hh"

#	include "Actor.hh"

#	include <map>
#	include <memory>

	namespace Entropy
	{
		namespace Asteria
		{
			using BaseCharacter = Entropy::Hecate::Character<Entropy::Hecate::tuple<Strength, Agility, Endurance, Perception, Magic, Willpower>>;

			using Entropy::Hecate::Check;
			using Entropy::Hecate::Modifier;
			using Entropy::Hecate::negative;
			using Entropy::Hecate::Untyped;
			using Entropy::Hecate::PercentType;
			using Entropy::Hecate::CostType;

			class Character :
				public BaseCharacter,
				public Actor
			{
				public:
					Character(const std::shared_ptr<Theia::GL::Texture> &, const Strength &, const Agility &, const Endurance &, const Perception &, const Magic &, const Willpower &);
					Health &Hp();
					const Health &Hp() const;
					bool isAlive() const;
					Check Attack(Character &);
					Check Defend();
					Check Flee(Character &);
					Check Chase();
					void Equip(const Weapon &);
					void Equip(const Armor &);
					void Equip(const Equipment &);
					void Unequip(const Equipment::Slot &);
				private:
					Health _health;
					std::shared_ptr<Weapon> _weapon;
					Armor::Type _armor;
					std::map<Equipment::Slot, std::shared_ptr<Equipment>> _equipment;
					static constexpr PercentType _default_damage = ENTROPY_ASTERIA_DEFAULT_MAX_DAMAGE;
			};
		}
	}

#endif
