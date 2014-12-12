#include <string>
#include <vector>

enum class suit
{spade, heart, diamond, club};

class card
{
public:
    card(const suit s, const size_t r);

    std::string to_string()const;

    size_t width()const
    {
        return width_;
    }

    size_t height()const
    {
        return height_;
    }
private:
    suit suit_;
    size_t rank_;

    size_t width_, height_;

    std::string contents_;
};
