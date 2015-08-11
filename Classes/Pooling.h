#pragma once

#include <vector>

namespace Homura
{
	template<typename T_DATA>
	class CPool
	{
	private:
		typedef std::vector<T_DATA*> DATA_CONTAINER;

	private:
		CPool(CPool& _Pool);
		CPool& operator=(CPool& _Pool);

	public:
		CPool(void){}
		virtual ~CPool(void){}

	public:
		// サイズほどデータを生成
		virtual void initialize(unsigned int _Size)
		{
			mDatas.clear();

			for (int i = 0; _Size > i; ++i)
			{
				mDatas.push_back(new T_DATA);
			}

			mUsedDataPosition = 0;
		}

		// 現在、作っているデータを全部除去
		void release(void)
		{
			for (int i = 0; mDatas.size() > i; ++i)
			{
				delete mDatas[i];
			}
		}

		// 生成しているデータ中使っていないでーたを返還
		// 生成してデータを返還するとこのデータはmUsingをtrueで変換
		// 使っていないデータがないと新しい作って返還
		T_DATA* newData(void)
		{
			if (mDatas.size() > mUsedDataPosition)
			{
				return mDatas[mUsedDataPosition++];
			}

			mDatas.push_back(new T_DATA);

			return mDatas[mUsedDataPosition++];
		}

		// 使っていたデータを返還
		// 返還してたデータはmUsingをfalseで変換
		bool deleteData(T_DATA* _Data)
		{
			// 返還するデータがNullの場合何もしてない
			if (nullptr == _Data)
			{
				return false;
			}
			for (int i = 0; mUsedDataPosition > i; ++i)
			{
				if (_Data == mDatas[i])
				{
					if (i != mUsedDataPosition - 1)
					{
						swap(i, mUsedDataPosition - 1);
					}

					--mUsedDataPosition;

					return true;
				}
			}

			return false;
		}

	protected:
		// 交換をしないとfalse
		bool swap(unsigned int _Index1, unsigned int _Index2)
		{
			// 交換するデータのインデックスが同じか
			if (_Index1 == _Index2)
			{
				return false;
			}
			// インデックスがサイズより大きいか
			else if (mDatas.size() <= _Index1 || mDatas.size() <= _Index2)
			{
				return false;
			}

			T_DATA* Temp = mDatas[_Index1];
			mDatas[_Index1] = mDatas[_Index2];
			mDatas[_Index2] = Temp;

			return true;
		}

	private:
		DATA_CONTAINER mDatas;
		int mUsedDataPosition;
	};
}

//Pool<ID> Pool