import random

# Number of professors and students
num_professors = 100
num_students = 200

# Open the file to write the output
with open("large_input.txt", "w") as f:
    # Write the number of professors and students
    f.write(f"{num_professors} {num_students}\n")
    
    # Generate random edges between professors and students
    for prof in range(1, num_professors + 1):
        num_edges = random.randint(1, 10)  # Each professor can be connected to 1-10 students
        students = random.sample(range(1, num_students + 1), num_edges)  # Randomly select students
        for student in students:
            f.write(f"Prof_{prof}: Stu_{student}\n")

print("Large input file 'large_input.txt' generated successfully.")
