struct SpellList {
    bool basicSpell,
    warriorSpell,
    mageSpell,
    mageSpell2,
    hunterSpell;
};

enum SPELL_enum{
    BASIC_SPELL,
    WARRIOR_SPELL,
    MAGE_SPELL,
    MAGE_SPELL_2,
    HUNTER_SPELL
};

class spell{
    private:

    public:

    int basicSpell(SpellList spellbook);
    int warriorSpell(SpellList spellbook);
    int mageSpell(SpellList spellbook);
    int mageSpell2(SpellList spellbook);
    int hunterSpell(SpellList spellbook);
};