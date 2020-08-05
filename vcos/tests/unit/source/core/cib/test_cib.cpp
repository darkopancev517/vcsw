#include "gtest/gtest.h"

#include "core/cib.hpp"

using namespace vc;

class TestCib : public testing::Test
{
protected:
    Cib *obj;

    virtual void SetUp()
    {
        obj = new Cib(4);
    }

    virtual void TearDown()
    {
        delete obj;
    }
};

TEST_F(TestCib, constructor_test)
{
    EXPECT_TRUE(obj);

    EXPECT_EQ(sizeof(Cib), sizeof(cib_t));
}

TEST_F(TestCib, functions_test)
{
    EXPECT_EQ(obj->full(), 0);
    EXPECT_EQ(obj->avail(), 0);
    EXPECT_EQ(obj->get_read_count(), 0);
    EXPECT_EQ(obj->get_write_count(), 0);

    EXPECT_EQ(obj->get_mask(), 3);

    EXPECT_EQ(obj->put(), 0);
    EXPECT_EQ(obj->put(), 1);
    EXPECT_EQ(obj->put(), 2);
    EXPECT_EQ(obj->put(), 3);

    EXPECT_EQ(obj->put(), -1); /* cib already full */
    EXPECT_EQ(obj->full(), 1);

    EXPECT_EQ(obj->put_unsafe(), 0); /* at this point cib was overwrite */

    EXPECT_EQ(obj->get_write_count(), 5);

    obj->init(4);

    EXPECT_EQ(obj->full(), 0);
    EXPECT_EQ(obj->avail(), 0);
    EXPECT_EQ(obj->get_read_count(), 0);
    EXPECT_EQ(obj->get_write_count(), 0);

    EXPECT_EQ(obj->get_mask(), 3);

    EXPECT_EQ(obj->put(), 0);
    EXPECT_EQ(obj->put(), 1);
    EXPECT_EQ(obj->put(), 2);
    EXPECT_EQ(obj->put(), 3);

    EXPECT_EQ(obj->peek(), 0);

    EXPECT_EQ(obj->full(), 1);
    EXPECT_EQ(obj->avail(), 4);
    EXPECT_EQ(obj->get_read_count(), 0);
    EXPECT_EQ(obj->get_write_count(), 4);

    EXPECT_EQ(obj->get(), 0);
    EXPECT_EQ(obj->get(), 1);

    EXPECT_EQ(obj->peek(), 2);

    EXPECT_EQ(obj->full(), 0);
    EXPECT_EQ(obj->avail(), 2);
    EXPECT_EQ(obj->get_read_count(), 2);
    EXPECT_EQ(obj->get_write_count(), 4);

    EXPECT_EQ(obj->get(), 2);
    EXPECT_EQ(obj->get(), 3);

    EXPECT_EQ(obj->peek(), -1);

    EXPECT_EQ(obj->full(), 0);
    EXPECT_EQ(obj->avail(), 0);
    EXPECT_EQ(obj->get_read_count(), 4);
    EXPECT_EQ(obj->get_write_count(), 4);
}
