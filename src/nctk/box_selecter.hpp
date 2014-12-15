#include "box.hpp"
#include <fstream>
#include <vector>

namespace nctk
{
    template <typename T>
    class box_selecter
    {
    public:
        box_selecter(const std::vector<box<T>>& hand)
            :hand_(hand)
        {
        }

        void draw()
        {
            for(size_t i = 0; i < hand_.size(); ++i)
            {
                if(std::find(selected_.begin(), selected_.end(), i))
                {
                    hand_.at(i).make_under(*this).draw();
                }
            }
        }

        void toggle(const size_t index)
        {
            auto may_found = std::find(selected_.begin(), selected_.end(), index);
            if(may_found == selected_.end()) // 未登録
            {
                selected_.push_back(index);
            }
            else
            {
                selected_.erase(may_found);
            }
        }

    private:
    
        const std::vector<box<T>>& hand_;
        std::vector<size_t> selected_;
    };

    class arrow
    {
    public:
        std::string to_string()const
        {
            return view_;
        }
        size_t height()const
        {
            return 6;
        }
        size_t width()const
        {
            return 11;
        }

    private:
        static std::ifstream ifs;
        static std::string view_;
    };
    std::ifstream arrow::ifs("arrow.txt");
    std::string   arrow::view_ = std::string(std::istreambuf_iterator<char>(arrow::ifs), std::istreambuf_iterator<char>());

}
