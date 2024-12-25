from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.orm import relationship, declarative_base, sessionmaker

Base = declarative_base()

class Category(Base):
    __tablename__ = "categories"
    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)
    products = relationship("Product", back_populates="category")

class Product(Base):
    __tablename__ = "products"
    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)
    price = Column(Integer)
    category_id = Column(Integer, ForeignKey("categories.id"))
    category = relationship("Category", back_populates="products")

# Подключение к базе и создание таблиц
engine = create_engine("postgresql+psycopg2://daria:3314@localhost/shop")
Base.metadata.create_all(engine)

# CRUD-операции
Session = sessionmaker(bind=engine)
session = Session()

# Create
category = Category(name="Flowers")
product = Product(name="Roses x5", price="1500", category=category)
session.add(category)
session.add(product)
session.commit()

# Read
category_from_db = session.query(Category).filter_by(name="Flowers").first()
print(category_from_db.name, category_from_db.products[0].name)

# Update
category_from_db.name = "Flowers XXL"
session.commit()

# Delete
# session.delete(category_from_db)
# session.commit()