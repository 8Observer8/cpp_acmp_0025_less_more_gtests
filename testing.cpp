#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <sstream>

class LogicError : public std::logic_error {
public:

    LogicError( ) : std::logic_error( "" ) {

    }

    virtual const char *what( ) const throw( ) {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw( ) {

    }

protected:
    std::string m_message;
};

class OutOfRange : public LogicError {
public:

    OutOfRange( int argument, int beginOfRange, int endOfRange ) {
        std::string str_argument, str_beginOfRange, str_endOfRange;

        str_argument = intToString( argument );
        str_beginOfRange = intToString( beginOfRange );
        str_endOfRange = intToString( endOfRange );

        m_message = "Argument " + str_argument + "doesn't hit in the range [" +
                str_beginOfRange + ", " + str_endOfRange + "]";
    }

private:

    std::string intToString( int number ) {
        std::stringstream stream;
        stream << number;
        return stream.str( );
    }
};

int less_or_more(int firstNumber, int secondNumber) throw( OutOfRange );

TEST( test001, outOfRangeTest ) {
    int firstNumber = 2000000000;
    int secondNumber = 0;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = 1;
    ASSERT_EQ( expected, actual );
}

TEST( test002, outOfRangeTest ) {
    int firstNumber = 0;
    int secondNumber = 2000000000;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = -1;
    ASSERT_EQ( expected, actual );
}

TEST( test003, outOfRangeTest ) {
    int firstNumber = -2000000000;
    int secondNumber = 0;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = -1;
    ASSERT_EQ( expected, actual );
}

TEST( test004, outOfRangeTest ) {
    int firstNumber = 0;
    int secondNumber = -2000000000;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = 1;
    ASSERT_EQ( expected, actual );
}

TEST( test005, outOfRangeTest ) {
    int firstNumber = 2000000001;
    int secondNumber = 0;

    ASSERT_THROW({
                     less_or_more( firstNumber, secondNumber );
                 }, OutOfRange);
}

TEST( test006, outOfRangeTest ) {
    int firstNumber = 0;
    int secondNumber = 2000000001;

    ASSERT_THROW({
                     less_or_more( firstNumber, secondNumber );
                 }, OutOfRange);
}

TEST( test007, outOfRangeTest ) {
    int firstNumber = -2000000001;
    int secondNumber = 0;

    ASSERT_THROW({
                     less_or_more( firstNumber, secondNumber );
                 }, OutOfRange);
}

TEST( test008, outOfRangeTest ) {
    int firstNumber = 0;
    int secondNumber = -2000000001;

    ASSERT_THROW({
                     less_or_more( firstNumber, secondNumber );
                 }, OutOfRange);
}

TEST( test009, normalTest ) {
    int firstNumber = 5;
    int secondNumber = 7;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = -1;
    ASSERT_EQ( expected, actual );
}


TEST( test010, normalTest ) {
    int firstNumber = -7;
    int secondNumber = -12;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = 1;
    ASSERT_EQ( expected, actual );
}

TEST( test011, normalTest ) {
    int firstNumber = 13;
    int secondNumber = 13;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = 0;
    ASSERT_EQ( expected, actual );
}

TEST( test012, normalTest ) {
    int firstNumber = 0;
    int secondNumber = 0;

    int actual = 0;
    ASSERT_NO_THROW({
                        actual = less_or_more( firstNumber, secondNumber );
                    });
    int expected = 0;
    ASSERT_EQ( expected, actual );
}

int main( int argc, char *argv[] ) {
    ::testing::InitGoogleTest( &argc, argv);
    return RUN_ALL_TESTS( );
}
