//потом допишу
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <cmath>
#include <filesystem>


// Observer
class IBattleObserver {
public:
    virtual ~IBattleObserver() = default;
    virtual void onKill(const std::string& killer, const std::string& victim) = 0;
};

class ConsoleObserver : public IBattleObserver {
public:
    void onKill(const std::string& killer, const std::string& victim) override {
        // В тестах перехватим через stringstream
    }
};

class FileObserver : public IBattleObserver {
    std::string filename;
public:
    explicit FileObserver(const std::string& fname) : filename(fname) {}
    void onKill(const std::string& killer, const std::string& victim) override {
        std::ofstream f(filename, std::ios::app);
        f << killer << " killed " << victim << "\n";
    }
};

// NPC базовый
class NPC {
protected:
    std::string name;
    int x, y;
    std::string type;
    bool alive = true;
    std::vector<IBattleObserver*> observers;

public:
    NPC(const std::string& n, int x_, int y_, const std::string& t)
        : name(n), x(x_), y(y_), type(t) {
        if (x < 0 || x > 500 || y < 0 || y > 500) {
            throw std::invalid_argument("Coordinates out of [0,500] bounds");
        }
    }

    virtual ~NPC() = default;

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    std::string getType() const { return type; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    void attach(IBattleObserver* obs) { observers.push_back(obs); }
    void notifyKill(const std::string& victim) {
        for (auto* obs : observers) {
            obs->onKill(name, victim);
        }
    }

    double distanceTo(const NPC& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    virtual bool accept(class BattleVisitor& visitor, NPC& other) = 0;
    virtual std::unique_ptr<NPC> clone() const = 0;
};

// Конкретные NPC
class Knight : public NPC {
public:
    Knight(const std::string& n, int x, int y) : NPC(n, x, y, "Knight") {}
    bool accept(BattleVisitor& visitor, NPC& other) override;
    std::unique_ptr<NPC> clone() const override { return std::make_unique<Knight>(*this); }
};

class Druid : public NPC {
public:
    Druid(const std::string& n, int x, int y) : NPC(n, x, y, "Druid") {}
    bool accept(BattleVisitor& visitor, NPC& other) override;
    std::unique_ptr<NPC> clone() const override { return std::make_unique<Druid>(*this); }
};

class Elf : public NPC {
public:
    Elf(const std::string& n, int x, int y) : NPC(n, x, y, "Elf") {}
    bool accept(BattleVisitor& visitor, NPC& other) override;
    std::unique_ptr<NPC> clone() const override { return std::make_unique<Elf>(*this); }
};

// Visitor
class BattleVisitor {
public:
    bool visit(Knight& a, NPC& b) {
        if (b.getType() == "Elf") {
            b.kill();
            a.notifyKill(b.getName());
            return true;
        }
        return false;
    }

    bool visit(Elf& a, NPC& b) {
        if (b.getType() == "Druid" || b.getType() == "Knight") {
            b.kill();
            a.notifyKill(b.getName());
            return true;
        }
        return false;
    }

    bool visit(Druid& a, NPC& b) {
        if (b.getType() == "Druid" && &a != &b) {
            b.kill();
            a.kill();
            a.notifyKill(b.getName());
            b.notifyKill(a.getName());
            return false; // оба мертвы
        }
        return false;
    }
};

// Реализация accept (после объявления BattleVisitor)
bool Knight::accept(BattleVisitor& visitor, NPC& other) {
    return visitor.visit(*this, other);
}
bool Druid::accept(BattleVisitor& visitor, NPC& other) {
    return visitor.visit(*this, other);
}
bool Elf::accept(BattleVisitor& visitor, NPC& other) {
    return visitor.visit(*this, other);
}

// Factory
class NPCFactory {
public:
    static std::unique_ptr<NPC> create(const std::string& type, const std::string& name, int x, int y) {
        if (type == "Knight" || type == "knight") return std::make_unique<Knight>(name, x, y);
        if (type == "Druid"  || type == "druid")  return std::make_unique<Druid>(name, x, y);
        if (type == "Elf"    || type == "elf")    return std::make_unique<Elf>(name, x, y);
        return nullptr;
    }
};


// ——— 1. Тесты NPC ———
TEST(NPCTest, ValidCoordinates) {
    EXPECT_NO_THROW({ Knight("K", 0, 0); });
    EXPECT_NO_THROW({ Druid("D", 500, 500); });
    EXPECT_NO_THROW({ Elf("E", 250, 250); });
}

TEST(NPCTest, InvalidCoordinatesThrow) {
    EXPECT_THROW({ Knight("K", -1, 0); }, std::invalid_argument);
    EXPECT_THROW({ Druid("D", 501, 250); }, std::invalid_argument);
    EXPECT_THROW({ Elf("E", 100, 600); }, std::invalid_argument);
}

// ——— 2. Тесты Factory ———
TEST(FactoryTest, CreatesAllTypes) {
    auto k = NPCFactory::create("Knight", "Arthas", 10, 20);
    auto d = NPCFactory::create("Druid", "Malfurion", 30, 40);
    auto e = NPCFactory::create("Elf", "Tyrande", 50, 60);

    ASSERT_NE(k, nullptr);
    ASSERT_NE(d, nullptr);
    ASSERT_NE(e, nullptr);

    EXPECT_EQ(k->getType(), "Knight");
    EXPECT_EQ(d->getType(), "Druid");
    EXPECT_EQ(e->getType(), "Elf");
}


// ——— 3. Тесты боя (Visitor) ———
TEST(BattleTest, KnightKillsElf) {
    Knight k("K", 0, 0);
    Elf e("E", 0, 0);
    BattleVisitor v;
    bool fought = k.accept(v, e);
    EXPECT_TRUE(fought);
    EXPECT_TRUE(k.isAlive());
    EXPECT_FALSE(e.isAlive());
}

TEST(BattleTest, ElfKillsKnight) {
    Elf e("E", 0, 0);
    Knight k("K", 0, 0);
    BattleVisitor v;
    bool fought = e.accept(v, k);
    EXPECT_TRUE(fought);
    EXPECT_TRUE(e.isAlive());
    EXPECT_FALSE(k.isAlive());
}

TEST(BattleTest, ElfKillsDruid) {
    Elf e("E", 0, 0);
    Druid d("D", 0, 0);
    BattleVisitor v;
    bool fought = e.accept(v, d);
    EXPECT_TRUE(fought);
    EXPECT_TRUE(e.isAlive());
    EXPECT_FALSE(d.isAlive());
}

TEST(BattleTest, SameTypeNoFight) {
    Knight k1("K1", 0, 0);
    Knight k2("K2", 0, 0);
    BattleVisitor v;
    bool fought = k1.accept(v, k2);
    EXPECT_FALSE(fought);
    EXPECT_TRUE(k1.isAlive());
    EXPECT_TRUE(k2.isAlive());
}

// ——— 4. Тесты Observer ———
class TestObserver : public IBattleObserver {
public:
    std::vector<std::pair<std::string, std::string>> kills;
    void onKill(const std::string& killer, const std::string& victim) override {
        kills.emplace_back(killer, victim);
    }
};

TEST(ObserverTest, NotificationsOnKill) {
    TestObserver obs;
    Knight k("K", 0, 0);
    Elf e("E", 0, 0);
    k.attach(&obs);
    e.attach(&obs);

    BattleVisitor v;
    k.accept(v, e);

    ASSERT_EQ(obs.kills.size(), 1);
    EXPECT_EQ(obs.kills[0].first, "K");
    EXPECT_EQ(obs.kills[0].second, "E");
}

TEST(ObserverTest, FileObserverWritesLog) {
    const char* fname = "test_log.txt";
    std::remove(fname);

    {
        FileObserver fileObs(fname);
        Knight k("K", 0, 0);
        Elf e("E", 0, 0);
        k.attach(&fileObs);
        e.attach(&fileObs);

        BattleVisitor v;
        k.accept(v, e);
    }

    std::ifstream f(fname);
    std::string line;
    std::getline(f, line);
    f.close();
    std::remove(fname);

    EXPECT_NE(line.find("K killed E"), std::string::npos);
}